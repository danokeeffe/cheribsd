/*-
 * Copyright (c) 2015-2019 SRI International
 * Copyright (c) 2002 Doug Rabson
 * Copyright (c) 2002 Marcel Moolenaar
 * All rights reserved.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract FA8750-10-C-0237
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of
 * the DARPA SSITH research programme.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include "opt_inet.h"
#include "opt_inet6.h"
#include "opt_ktrace.h"
#include "opt_posix.h"
#include "opt_capsicum.h"

#include <sys/param.h>
#include <sys/bus.h>
#include <sys/capsicum.h>
#include <sys/clock.h>
#include <sys/exec.h>
#include <sys/fcntl.h>
#include <sys/filedesc.h>
#include <sys/imgact.h>
#include <sys/imgact_elf.h>
#include <sys/jail.h>
#include <sys/kernel.h>
#include <sys/limits.h>
#include <sys/linker.h>
#include <sys/lock.h>
#include <sys/malloc.h>
#include <sys/file.h>		/* Must come after sys/malloc.h */
#include <sys/imgact.h>
#include <sys/mbuf.h>
#include <sys/mman.h>
#include <sys/module.h>
#include <sys/mount.h>
#include <sys/mutex.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/procctl.h>
#include <sys/posix4.h>
#include <sys/ptrace.h>
#include <sys/reboot.h>
#include <sys/resource.h>
#include <sys/resourcevar.h>
#include <sys/selinfo.h>
#include <sys/eventvar.h>	/* Must come after sys/selinfo.h */
#include <sys/pipe.h>		/* Must come after sys/selinfo.h */
#include <sys/signal.h>
#include <sys/ktrace.h>		/* Must come after sys/signal.h */
#include <sys/signalvar.h>
#include <sys/smp.h>
#include <sys/socket.h>
#include <sys/socketvar.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/syscallsubr.h>
#include <sys/sysctl.h>
#include <sys/sysent.h>
#include <sys/sysproto.h>
#include <sys/systm.h>
#include <sys/thr.h>
#include <sys/unistd.h>
#include <sys/ucontext.h>
#include <sys/user.h>
#include <sys/umtx.h>
#include <sys/uuid.h>
#include <sys/vnode.h>
#include <sys/vdso.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>

#ifdef INET
#include <netinet/in.h>
#endif

#include <vm/vm.h>
#include <vm/vm_param.h>
#include <vm/pmap.h>
#include <vm/vm_map.h>
#include <vm/vm_object.h>
#include <vm/vm_extern.h>

#include <machine/cpu.h>
#include <machine/elf.h>

#include <security/audit/audit.h>

#include <cheri/cheri.h>

#include <compat/freebsd64/freebsd64.h>
#include <compat/freebsd64/freebsd64_util.h>
#include <compat/freebsd64/freebsd64_signal.h>
#include <compat/freebsd64/freebsd64_proto.h>
#include <compat/freebsd64/freebsd64_syscall.h>

MALLOC_DECLARE(M_KQUEUE);

struct sf_hdtr64 {
	struct iovec64 *headers;
	int hdr_cnt;
	struct iovec64 *trailers;
	int trl_cnt;
};

FEATURE(compat_freebsd64_abi, "Compatible 64-bit FreeBSD system call ABI");

static int freebsd64_kevent_copyout(void *arg, kkevent_t *kevp, int count);
static int freebsd64_kevent_copyin(void *arg, kkevent_t *kevp, int count);

int
freebsd64_wait4(struct thread *td, struct freebsd64_wait4_args *uap)
{

	return (kern_wait4(td, uap->pid, __USER_CAP_OBJ(uap->status),
	    uap->options, __USER_CAP_OBJ(uap->rusage)));
}

int
freebsd64_wait6(struct thread *td, struct freebsd64_wait6_args *uap)
{
	_siginfo_t si, *sip;
	struct siginfo64 si64;
	int error;
	
	if (uap->info != NULL) {
		sip = &si;
		bzero(sip, sizeof(*sip));
	} else
		sip = NULL;
	error = user_wait6(td, uap->idtype, uap->id,
	    __USER_CAP_OBJ(uap->status), uap->options,
	    __USER_CAP_OBJ(uap->wrusage), sip);
	if (uap->info != NULL && error == 0) {
		siginfo_to_siginfo64(&si, &si64);
		error = copyout(&si64, uap->info, sizeof(si64));
	}
	return (error);
}

int
freebsd64_execve(struct thread *td, struct freebsd64_execve_args *uap)
{
	struct image_args eargs;
	struct vmspace *oldvmspace;
	int error;

	error = pre_execve(td, &oldvmspace);
	if (error != 0)
		return (error);
	error = exec_copyin_args(&eargs, __USER_CAP_STR(uap->fname),
	    UIO_USERSPACE, __USER_CAP_UNBOUND(uap->argv),
	    __USER_CAP_UNBOUND(uap->envv));
	if (error == 0)
		error = kern_execve(td, &eargs, NULL);
	post_execve(td, error, oldvmspace);
	return (error);
}

int
freebsd64_fexecve(struct thread *td, struct freebsd64_fexecve_args *uap)
{
	struct image_args eargs;
	struct vmspace *oldvmspace;
	int error;

	error = pre_execve(td, &oldvmspace);
	if (error != 0)
		return (error);
	error = exec_copyin_args(&eargs, NULL, UIO_SYSSPACE,
	    __USER_CAP_UNBOUND(uap->argv), __USER_CAP_UNBOUND(uap->envv));
	if (error == 0) {
		eargs.fd = uap->fd;
		error = kern_execve(td, &eargs, NULL);
	}
	post_execve(td, error, oldvmspace);
	return (error);
}

/*
 * Copy 'count' items into the destination list pointed to by uap->eventlist.
 */
static int
freebsd64_kevent_copyout(void *arg, kkevent_t *kevp, int count)
{
	struct freebsd64_kevent_args *uap;
	struct kevent64 ks64[KQ_NEVENTS];
	int error, i;

	KASSERT(count <= KQ_NEVENTS, ("count (%d) > KQ_NEVENTS", count));
	uap = (struct freebsd64_kevent_args *)arg;

	for (i = 0; i < count; i++) {
		ks64[i].ident = kevp[i].ident;
		ks64[i].filter = kevp[i].filter;
		ks64[i].flags = kevp[i].flags;
		ks64[i].fflags = kevp[i].fflags;
		ks64[i].data = kevp[i].data;
		ks64[i].udata = (__cheri_addr vaddr_t)kevp[i].udata;
		memcpy(&ks64[i].ext[0], &kevp->ext[0], sizeof(kevp->ext));
	}
	error = copyout(ks64, uap->eventlist, count * sizeof(*ks64));
	if (error == 0)
		uap->eventlist += count;
	return (error);
}

/*
 * Copy 'count' items from the list pointed to by uap->changelist.
 */
static int
freebsd64_kevent_copyin(void *arg, kkevent_t *kevp, int count)
{
	struct freebsd64_kevent_args *uap;
	struct kevent64 ks64[KQ_NEVENTS];
	int error, i;

	KASSERT(count <= KQ_NEVENTS, ("count (%d) > KQ_NEVENTS", count));
	uap = (struct freebsd64_kevent_args *)arg;

	error = copyin(uap->changelist, ks64, count * sizeof(*ks64));
	if (error != 0)
		return (error);
	for (i = 0; i < count; i++) {
		kevp[i].ident = ks64[i].ident;
		kevp[i].filter = ks64[i].filter;
		kevp[i].flags = ks64[i].flags;
		kevp[i].fflags = ks64[i].fflags;
		kevp[i].data = ks64[i].data;
		/* Store untagged. */
		kevp[i].udata = (void * __capability)(intcap_t)ks64[i].udata;
		memcpy(&kevp[i].ext[0], &ks64->ext[0], sizeof(ks64->ext));
	}
	uap->changelist += count;
	return (error);
}

int
freebsd64_kevent(struct thread *td, struct freebsd64_kevent_args *uap)
{
	struct timespec ts, *tsp;
	struct kevent_copyops k_ops = { uap,
					freebsd64_kevent_copyout,
					freebsd64_kevent_copyin};
	int error;

	if (uap->timeout) {
		error = copyin(uap->timeout, &ts, sizeof(ts));
		if (error)
			return (error);
		tsp = &ts;
	} else
		tsp = NULL;
	error = kern_kevent(td, uap->fd, uap->nchanges, uap->nevents,
	    &k_ops, tsp);
	return (error);
}

int
freebsd64_copyinuio(struct iovec64 * __capability iovp, u_int iovcnt,
    struct uio **uiop)
{
	struct iovec64 iov64;
	kiovec_t *iov;
	struct uio *uio;
	size_t iovlen;
	int error, i;

	*uiop = NULL;
	if (iovcnt > UIO_MAXIOV)
		return (EINVAL);
	iovlen = iovcnt * sizeof(kiovec_t);
	uio = malloc(iovlen + sizeof(*uio), M_IOV, M_WAITOK);
	iov = (kiovec_t *)(uio + 1);
	for (i = 0; i < iovcnt; i++) {
		error = copyin_c(&iovp[i], &iov64, sizeof(iov64));
		if (error) {
			free(uio, M_IOV);
			return (error);
		}
		IOVEC_INIT(&iov[i],
		    PURECAP_KERNEL_USER_CAP(iov64.iov_base, iov64.iov_len),
		    iov64.iov_len);
	}
	uio->uio_iov = iov;
	uio->uio_iovcnt = iovcnt;
	uio->uio_segflg = UIO_USERSPACE;
	uio->uio_offset = -1;
	uio->uio_resid = 0;
	for (i = 0; i < iovcnt; i++) {
		if (iov[i].iov_len > SIZE_MAX - uio->uio_resid) {
			free(uio, M_IOV);
			return (EINVAL);
		}
		uio->uio_resid += iov[i].iov_len;
	}
	*uiop = uio;
	return (0);
}

int
freebsd64_copyiniov(struct iovec64 * __capability iov64, u_int iovcnt,
    kiovec_t **iovp, int error)
{
	uiovec_t useriov;
	kiovec_t *iovs;
	size_t iovlen;
	int i;

	*iovp = NULL;
	if (iovcnt > UIO_MAXIOV)
		return (error);
	iovlen = iovcnt * sizeof(kiovec_t);
	iovs = malloc(iovlen, M_IOV, M_WAITOK);
	for (i = 0; i < iovcnt; i++) {
		error = copyin_c(iov64 + i, &useriov, sizeof(useriov));
		if (error) {
			free(iovs, M_IOV);
			return (error);
		}
		IOVEC_INIT(iovs + i, useriov.iov_base, useriov.iov_len);
	}
	*iovp = iovs;
	return (0);
}

static int
freebsd64_copyin_hdtr(const struct sf_hdtr64 * __capability uhdtr,
    ksf_hdtr_t *hdtr)
{
	struct sf_hdtr64 hdtr64;
	int error;

	error = copyin_c(uhdtr, &hdtr64, sizeof(hdtr64));
	if (error != 0)
		return (error);
	hdtr->headers = (void * __capability)__USER_CAP_ARRAY(hdtr64.headers,
	    hdtr64.hdr_cnt);
	hdtr->hdr_cnt = hdtr64.hdr_cnt;
	hdtr->trailers = (void * __capability)__USER_CAP_ARRAY(hdtr64.trailers,
	    hdtr64.trl_cnt);
	hdtr->hdr_cnt = hdtr64.trl_cnt;

	return (0);
}

int freebsd64_sendfile(struct thread *td, struct freebsd64_sendfile_args *uap)
{

	return (kern_sendfile(td, uap->fd, uap->s, uap->offset, uap->nbytes,
	    __USER_CAP_OBJ(uap->hdtr), __USER_CAP_OBJ(uap->sbytes),
	    uap->flags, 0, (copyin_hdtr_t *)freebsd64_copyin_hdtr,
	    (copyinuio_t *)freebsd64_copyinuio));
}

#if 0
int
cheriabi_jail(struct thread *td, struct cheriabi_jail_args *uap)
{
}
#endif

int
freebsd64_jail_set(struct thread *td, struct freebsd64_jail_set_args *uap)
{

	return (user_jail_set(td, __USER_CAP_ARRAY(uap->iovp, uap->iovcnt),
	    uap->iovcnt, uap->flags, (copyinuio_t *)freebsd64_copyinuio));
}

static int
freebsd64_updateiov(const struct uio *uiop, struct iovec64 * __capability iovp)
{
	int i, error;

	for (i = 0; i < uiop->uio_iovcnt; i++) {
		error = suword_c(&iovp[i].iov_len, uiop->uio_iov[i].iov_len);
		if (error != 0)
			return (error);
	}
	return (0);
}

int
freebsd64_jail_get(struct thread *td, struct freebsd64_jail_get_args *uap)
{

	return (user_jail_get(td, __USER_CAP_ARRAY(uap->iovp, uap->iovcnt),
	    uap->iovcnt, uap->flags, (copyinuio_t *)freebsd64_copyinuio,
	    (updateiov_t *)freebsd64_updateiov));
}

int
freebsd64_sigreturn(struct thread *td, struct freebsd64_sigreturn_args *uap)
{
	ucontext64_t uc;
	int error;

	error = copyin(uap->sigcntxp, &uc, sizeof(uc));
	if (error != 0)
		return (error);

	error = freebsd64_set_mcontext(td, &uc.uc_mcontext);
	if (error != 0)
		return (error);

	kern_sigprocmask(td, SIG_SETMASK, &uc.uc_sigmask, NULL, 0);

	return (EJUSTRETURN);
}

#define UCC_COPY_SIZE	offsetof(ucontext64_t, uc_link)

int
freebsd64_getcontext(struct thread *td, struct freebsd64_getcontext_args *uap)
{
	ucontext64_t uc;

	if (uap->ucp == NULL)
		return (EINVAL);

	bzero(&uc, sizeof(uc));
	freebsd64_get_mcontext(td, &uc.uc_mcontext, GET_MC_CLEAR_RET);
	PROC_LOCK(td->td_proc);
	uc.uc_sigmask = td->td_sigmask;
	PROC_UNLOCK(td->td_proc);
	return (copyout(&uc, uap->ucp, UCC_COPY_SIZE));
}

int
freebsd64_setcontext(struct thread *td, struct freebsd64_setcontext_args *uap)
{
	ucontext64_t uc;
	int ret;

	if (uap->ucp == NULL)
		return (EINVAL);
	if ((ret = copyin(uap->ucp, &uc, UCC_COPY_SIZE)) != 0)
		return (ret);
	if ((ret = freebsd64_set_mcontext(td, &uc.uc_mcontext)) != 0)
		return (ret);
	kern_sigprocmask(td, SIG_SETMASK,
	    &uc.uc_sigmask, NULL, 0);

	return (EJUSTRETURN);
}

int
freebsd64_swapcontext(struct thread *td, struct freebsd64_swapcontext_args *uap)
{
	ucontext64_t uc;
	int ret;

	if (uap->oucp == NULL || uap->ucp == NULL)
		return (EINVAL);

	bzero(&uc, sizeof(uc));
	freebsd64_get_mcontext(td, &uc.uc_mcontext, GET_MC_CLEAR_RET);
	PROC_LOCK(td->td_proc);
	uc.uc_sigmask = td->td_sigmask;
	PROC_UNLOCK(td->td_proc);
	if ((ret = copyout(&uc, uap->oucp, UCC_COPY_SIZE)) != 0)
		return (ret);
	if ((ret = copyin(uap->ucp, &uc, UCC_COPY_SIZE)) != 0)
		return (ret);
	if ((ret = freebsd64_set_mcontext(td, &uc.uc_mcontext)) != 0)
		return (ret);
	kern_sigprocmask(td, SIG_SETMASK, &uc.uc_sigmask, NULL, 0);

	return (EJUSTRETURN);
}

int
freebsd64_procctl(struct thread *td, struct freebsd64_procctl_args *uap)
{

	return (user_procctl(td, uap->idtype, uap->id, uap->com,
	    __USER_CAP_UNBOUND(uap->data)));
}

int
freebsd64_nmount(struct thread *td, struct freebsd64_nmount_args *uap)
{

	return (kern_nmount(td, __USER_CAP_ARRAY(uap->iovp, uap->iovcnt),
	    uap->iovcnt, uap->flags, (copyinuio_t *)freebsd64_copyinuio));
}

register_t *
freebsd64_copyout_strings(struct image_params *imgp)
{

	/* XXX: works while exec_copyout_strings isn't cheriabi aware */
	return (exec_copyout_strings(imgp));
}

int
freebsd64_mount(struct thread *td, struct freebsd64_mount_args *uap)
{

	/* XXX: probably need to fill this in... :-( */
	return (ENOSYS);
}

int
freebsd64_kenv(struct thread *td, struct freebsd64_kenv_args *uap)
{

	return (kern_kenv(td, uap->what, __USER_CAP_STR(uap->name),
	    __USER_CAP_STR(uap->value), uap->len));
}

int
freebsd64_kbounce(struct thread *td, struct freebsd64_kbounce_args *uap)
{
	void * bounce;
	void * dst = uap->dst;
	const void * src = uap->src;
	size_t len = uap->len;
	int flags = uap->flags;
	int error;

	if (len > IOSIZE_MAX)
		return (EINVAL);
	if (flags != 0)
		return (EINVAL);
	if (src == NULL || dst == NULL)
		return (EINVAL);

	bounce = malloc(len, M_TEMP, M_WAITOK);
	error = copyin(src, bounce, len);
	if (error != 0)
		goto error;
	error = copyout(bounce, dst, len);
error:
	free(bounce, M_TEMP);
	return (error);
}

/*
 * audit_syscalls.c
 */
int
freebsd64_audit(struct thread *td, struct freebsd64_audit_args *uap)
{

#ifdef	AUDIT
	return (kern_audit(td, __USER_CAP(uap->record, uap->length),
	    uap->length));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_auditon(struct thread *td, struct freebsd64_auditon_args *uap)
{

#ifdef	AUDIT
	return (kern_auditon(td, uap->cmd, __USER_CAP(uap->data, uap->length),
	    uap->length));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_getauid(struct thread *td, struct freebsd64_getauid_args *uap)
{

#ifdef	AUDIT
	return (kern_getauid(td, __USER_CAP_OBJ(uap->auid)));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_setauid(struct thread *td, struct freebsd64_setauid_args *uap)
{

#ifdef	AUDIT
	return (kern_setauid(td, __USER_CAP_OBJ(uap->auid)));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_getaudit(struct thread *td, struct freebsd64_getaudit_args *uap)
{

#ifdef	AUDIT
	return (kern_getaudit(td, __USER_CAP_OBJ(uap->auditinfo)));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_setaudit(struct thread *td, struct freebsd64_setaudit_args *uap)
{

#ifdef	AUDIT
	return (kern_setaudit(td, __USER_CAP_OBJ(uap->auditinfo)));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_getaudit_addr(struct thread *td,
    struct freebsd64_getaudit_addr_args *uap)
{

#ifdef	AUDIT
	return (kern_getaudit_addr(td,
	    __USER_CAP(uap->auditinfo_addr, uap->length), uap->length));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_setaudit_addr(struct thread *td,
    struct freebsd64_setaudit_addr_args *uap)
{

#ifdef	AUDIT
	return (kern_setaudit_addr(td, 
	    __USER_CAP(uap->auditinfo_addr, uap->length), uap->length));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_auditctl(struct thread *td, struct freebsd64_auditctl_args *uap)
{

#ifdef	AUDIT
	return (kern_auditctl(td, __USER_CAP_STR(uap->path)));
#else
	return (ENOSYS);
#endif
}


/*
 * kern_acct.c
 */

int
freebsd64_acct(struct thread *td, struct freebsd64_acct_args *uap)
{

	return (kern_acct(td, __USER_CAP_STR(uap->path)));
}

/*
 * kern_fork.c
 */
int
freebsd64_pdfork(struct thread *td, struct freebsd64_pdfork_args *uap)
{

	return (kern_pdfork(td, __USER_CAP_OBJ(uap->fdp), uap->flags));
}

/*
 * kern_cpuset.c
 */
int
freebsd64_cpuset(struct thread *td, struct freebsd64_cpuset_args *uap)
{

	return (kern_cpuset(td, __USER_CAP_OBJ(uap->setid)));
}

int
freebsd64_cpuset_getid(struct thread *td,
    struct freebsd64_cpuset_getid_args *uap)
{

	return (kern_cpuset_getid(td, uap->level, uap->which, uap->id,
	    __USER_CAP_OBJ(uap->setid)));
}

int
freebsd64_cpuset_getaffinity(struct thread *td,
    struct freebsd64_cpuset_getaffinity_args *uap)
{

	return (kern_cpuset_getaffinity(td, uap->level, uap->which,
	    uap->id, uap->cpusetsize, __USER_CAP(uap->mask, uap->cpusetsize)));
}

int
freebsd64_cpuset_setaffinity(struct thread *td,
    struct freebsd64_cpuset_setaffinity_args *uap)
{

	return (kern_cpuset_setaffinity(td, uap->level, uap->which, uap->id,
	    uap->cpusetsize, __USER_CAP(uap->mask, uap->cpusetsize)));
}

int
freebsd64_cpuset_getdomain(struct thread *td,
    struct freebsd64_cpuset_getdomain_args *uap)
{

	return (kern_cpuset_getdomain(td, uap->level, uap->which,
	    uap->id, uap->domainsetsize,
	    __USER_CAP(uap->mask, uap->domainsetsize),
	    __USER_CAP_OBJ(uap->policy)));
}

int
freebsd64_cpuset_setdomain(struct thread *td,
    struct freebsd64_cpuset_setdomain_args *uap)
{

	return (kern_cpuset_setdomain(td, uap->level, uap->which,
	    uap->id, uap->domainsetsize,
	    __USER_CAP(uap->mask, uap->domainsetsize),
	    uap->policy));
}

/*
 * kern_descrip.c
 */
int
freebsd64_fcntl(struct thread *td, struct freebsd64_fcntl_args *uap)
{
	intcap_t arg;

	switch (uap->cmd) {
	case F_GETLK:
	case F_OGETLK:
	case F_OSETLK:
	case F_OSETLKW:
	case F_SETLK:
	case F_SETLKW:
	case F_SETLK_REMOTE:
		arg = (intcap_t)__USER_CAP_UNBOUND((void *)uap->arg);
		break;
	default:
		arg = (intcap_t)uap->arg;
	}

	return (kern_fcntl_freebsd(td, uap->fd, uap->cmd, arg));
}

int
freebsd64_fstat(struct thread *td, struct freebsd64_fstat_args *uap)
{

	return (user_fstat(td, uap->fd, __USER_CAP_OBJ(uap->sb)));
}

/*
 * kern_ktrace.c
 */

int
freebsd64_ktrace(struct thread *td, struct freebsd64_ktrace_args *uap)
{

	return (kern_ktrace(td, __USER_CAP_STR(uap->fname), uap->ops,
	    uap->facs, uap->pid));
}

int
freebsd64_utrace(struct thread *td, struct freebsd64_utrace_args *uap)
{

	return (kern_utrace(td, __USER_CAP(uap->addr, uap->len),
	    uap->len));
}

/*
 * kern_linker.c
 */

int
freebsd64_kldload(struct thread *td, struct freebsd64_kldload_args *uap)
{

	return (user_kldload(td, __USER_CAP_STR(uap->file)));
}

int
freebsd64_kldfind(struct thread *td, struct freebsd64_kldfind_args *uap)
{

	return (kern_kldfind(td, __USER_CAP_STR(uap->file)));
}

int
freebsd64_kldstat(struct thread *td, struct freebsd64_kldstat_args *uap)
{
        struct kld_file_stat stat;
        struct kld_file_stat64 stat64;
        int error, version;

        error = copyin(&uap->stat->version, &version, sizeof(version));
	if (error != 0)
                return (error);
        if (version != sizeof(struct kld_file_stat64))
                return (EINVAL);

        error = kern_kldstat(td, uap->fileid, &stat);
        if (error != 0)
                return (error);

        bcopy(&stat.name[0], &stat64.name[0], sizeof(stat.name));
        CP(stat, stat64, refs);
        CP(stat, stat64, id);
	stat64.address = (__cheri_addr uint64_t)stat.address;
        CP(stat, stat64, size);
        bcopy(&stat.pathname[0], &stat64.pathname[0], sizeof(stat.pathname));
        return (copyout(&stat64, uap->stat, version));
}

int
freebsd64_kldsym(struct thread *td, struct freebsd64_kldsym_args *uap)
{
	struct kld_sym_lookup64 lookup;
	int error;

	error = copyin(uap->data, &lookup, sizeof(lookup));
	if (error != 0)
		return (error);
	if (lookup.version != sizeof(lookup) ||
	    uap->cmd != KLDSYM_LOOKUP)
		return (EINVAL);
	error = kern_kldsym(td, uap->fileid, uap->cmd,
	    __USER_CAP_STR(lookup.symname), &lookup.symvalue, &lookup.symsize);
	if (error != 0)
		return (error);
	error = copyout(&lookup, uap->data, sizeof(lookup));

	return (error);
}

/*
 * kern_loginclass.c
 */
int
freebsd64_getloginclass(struct thread *td,
    struct freebsd64_getloginclass_args *uap)
{

	return (kern_getloginclass(td, __USER_CAP(uap->namebuf, uap->namelen),
	    uap->namelen));
}

int
freebsd64_setloginclass(struct thread *td,
    struct freebsd64_setloginclass_args *uap)
{

	return (kern_setloginclass(td, __USER_CAP_STR(uap->namebuf)));
}

int
freebsd64_uuidgen(struct thread *td, struct freebsd64_uuidgen_args *uap)
{

	return (user_uuidgen(td, __USER_CAP_ARRAY(uap->store, uap->count),
	    uap->count));
}

/*
 * kern_module.c
 */
int
freebsd64_modfind(struct thread *td, struct freebsd64_modfind_args *uap)
{

	return (kern_modfind(td, __USER_CAP_STR(uap->name)));
}

int
freebsd64_modstat(struct thread *td, struct freebsd64_modstat_args *uap)
{

	return (kern_modstat(td, uap->modid, __USER_CAP_OBJ(uap->stat)));
}

/*
 * kern_prot.c
 */
int
freebsd64_getgroups(struct thread *td, struct freebsd64_getgroups_args *uap)
{

	return (kern_getgroups(td, uap->gidsetsize,
	    __USER_CAP_ARRAY(uap->gidset, uap->gidsetsize)));
}

int
freebsd64_setgroups(struct thread *td, struct freebsd64_setgroups_args *uap)
{

	return (user_setgroups(td, uap->gidsetsize,
	    __USER_CAP_ARRAY(uap->gidset, uap->gidsetsize)));
}

int
freebsd64_getresuid(struct thread *td, struct freebsd64_getresuid_args *uap)
{

	return (kern_getresuid(td, __USER_CAP_OBJ(uap->ruid),
	    __USER_CAP_OBJ(uap->euid), __USER_CAP_OBJ(uap->suid)));
}

int
freebsd64_getresgid(struct thread *td, struct freebsd64_getresgid_args *uap)
{

	return (kern_getresgid(td, __USER_CAP_OBJ(uap->rgid),
	    __USER_CAP_OBJ(uap->egid), __USER_CAP_OBJ(uap->sgid)));
}

int
freebsd64_getlogin(struct thread *td, struct freebsd64_getlogin_args *uap)
{

	return (kern_getlogin(td, __USER_CAP(uap->namebuf, uap->namelen),
	    uap->namelen));
}

int
freebsd64_setlogin(struct thread *td, struct freebsd64_setlogin_args *uap)
{

	return (kern_setlogin(td, __USER_CAP_STR(uap->namebuf)));
}

/*
 * kern_rctl.c
 */
int
freebsd64_rctl_get_racct(struct thread *td,
    struct freebsd64_rctl_get_racct_args *uap)
{

#ifdef RCTL
	return (kern_rctl_get_racct(td, __USER_CAP(uap->inbufp, uap->inbuflen),
	    uap->inbuflen, __USER_CAP(uap->outbufp, uap->outbuflen),
	    uap->outbuflen));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_rctl_get_rules(struct thread *td,
    struct freebsd64_rctl_get_rules_args *uap)
{

#ifdef RCTL
	return (kern_rctl_get_rules(td, __USER_CAP(uap->inbufp, uap->inbuflen),
	    uap->inbuflen, __USER_CAP(uap->outbufp, uap->outbuflen),
	    uap->outbuflen));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_rctl_get_limits(struct thread *td,
    struct freebsd64_rctl_get_limits_args *uap)
{

#ifdef RCTL
	return (kern_rctl_get_limits(td, __USER_CAP(uap->inbufp, uap->inbuflen),
	    uap->inbuflen, __USER_CAP(uap->outbufp, uap->outbuflen),
	    uap->outbuflen));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_rctl_add_rule(struct thread *td,
    struct freebsd64_rctl_add_rule_args *uap)
{

#ifdef RCTL
	return (kern_rctl_add_rule(td, __USER_CAP(uap->inbufp, uap->inbuflen),
	    uap->inbuflen, __USER_CAP(uap->outbufp, uap->outbuflen),
	    uap->outbuflen));
#else
	return (ENOSYS);
#endif
}

int
freebsd64_rctl_remove_rule(struct thread *td,
    struct freebsd64_rctl_remove_rule_args *uap)
{

#ifdef RCTL
	return (kern_rctl_remove_rule(td,
	    __USER_CAP(uap->inbufp, uap->inbuflen), uap->inbuflen,
	    __USER_CAP(uap->outbufp, uap->outbuflen), uap->outbuflen));
#else
	return (ENOSYS);
#endif
}

/*
 * kern_resource.h
 */
int
freebsd64_rtprio_thread(struct thread *td,
    struct freebsd64_rtprio_thread_args *uap)
{

	return (kern_rtprio_thread(td, uap->function, uap->lwpid,
	    __USER_CAP_OBJ(uap->rtp)));
}

int
freebsd64_rtprio(struct thread *td, struct freebsd64_rtprio_args *uap)
{

	return (kern_rtprio(td, uap->function, uap->pid,
	    __USER_CAP_OBJ(uap->rtp)));
}

int
freebsd64_setrlimit(struct thread *td, struct freebsd64___setrlimit_args *uap)
{
	struct rlimit alim;
	int error;

	error = copyin(uap->rlp, &alim, sizeof(struct rlimit));
	if (error != 0)
		return (error);
	return (kern_setrlimit(td, uap->which, &alim));
}

int
freebsd64_getrlimit(struct thread *td, struct freebsd64___getrlimit_args *uap)
{
	struct rlimit rlim;
	int error;

	if (uap->which >= RLIM_NLIMITS)
		return (EINVAL);
	lim_rlimit(td, uap->which, &rlim);
	error = copyout(&rlim, uap->rlp, sizeof(struct rlimit));
	return (error);
}

int
freebsd64_getrusage(struct thread *td, struct freebsd64_getrusage_args *uap)
{
	struct rusage ru;
	int error;

	error = kern_getrusage(td, uap->who, &ru);
	if (error == 0)
		error = copyout(&ru, uap->rusage, sizeof(struct rusage));
	return (error);
}

/*
 * kern_sysctl.c
 */

int
freebsd64___sysctl(struct thread *td, struct freebsd64___sysctl_args *uap)
{

	return (kern_sysctl(td, __USER_CAP_ARRAY(uap->name, uap->namelen),
	    uap->namelen, __USER_CAP_UNBOUND(uap->old),
	    __USER_CAP_OBJ(uap->oldlenp), __USER_CAP(uap->new, uap->newlen),
	    uap->newlen, 0));
}

/*
 * kern_thr.c
 */

struct thr_create_initthr_args64 {
	ucontext64_t ctx;
	long *tid;
};

static int
freebsd64_thr_create_initthr(struct thread *td, void *thunk)
{
	struct thr_create_initthr_args64 *args;

	args = thunk;
	if (args->tid != NULL && suword(args->tid, td->td_tid) != 0)
		return (EFAULT);

	return (freebsd64_set_mcontext(td, &args->ctx.uc_mcontext));
}

int
freebsd64_thr_create(struct thread *td, struct freebsd64_thr_create_args *uap)
{
	struct thr_create_initthr_args64 args;
	int error;

	if ((error = copyin(uap->ctx, &args.ctx, sizeof(args.ctx))))
		return (error);
	args.tid = uap->id;
	return (thread_create(td, NULL, freebsd64_thr_create_initthr, &args));
}

int
freebsd64_thr_self(struct thread *td, struct freebsd64_thr_self_args *uap)
{
	int error;

	error = suword(uap->id, td->td_tid);
	if (error == -1)
		return (EFAULT);
	return (0);
}

int
freebsd64_thr_exit(struct thread *td, struct freebsd64_thr_exit_args *uap)
{

	umtx_thread_exit(td);

	/* Signal userland that it can free the stack. */
	if (uap->state != NULL) {
		suword(uap->state, 1);
		kern_umtx_wake(td, __USER_CAP_OBJ(uap->state), INT_MAX, 0);
	}

	return (kern_thr_exit(td));
}

int
freebsd64_thr_suspend(struct thread *td, struct freebsd64_thr_suspend_args *uap)
{
	struct timespec ts, *tsp;
	int error;

	tsp = NULL;
	if (uap->timeout != NULL) {
		error = umtx_copyin_timeout(__USER_CAP_OBJ(uap->timeout), &ts);
		if (error != 0)
			return (error);
		tsp = &ts;
	}

	return (kern_thr_suspend(td, tsp));
}

int
freebsd64_thr_set_name(struct thread *td,
    struct freebsd64_thr_set_name_args *uap)
{

	return (kern_thr_set_name(td, uap->id, __USER_CAP_STR(uap->name)));
}

static int
freebsd64_thr_new_initthr(struct thread *td, void *thunk)
{
	stack_t stack;
	struct thr_param64 *param = thunk;
	long *child_tid = PURECAP_KERNEL_USER_CAP(param->child_tid,
	    sizeof(long));
	long *parent_tid = PURECAP_KERNEL_USER_CAP(param->parent_tid,
	    sizeof(long));

	if ((child_tid != NULL && suword(child_tid, td->td_tid)) ||
	    (parent_tid != NULL && suword(parent_tid, td->td_tid)))
		return (EFAULT);
	stack.ss_sp = __USER_CAP_UNBOUND(param->stack_base);
	stack.ss_size = param->stack_size;
	cpu_set_upcall(td, PURECAP_KERNEL_USER_CODE_CAP(param->start_func),
	    PURECAP_KERNEL_USER_CAP_UNBOUND(param->arg), &stack);
	return (cpu_set_user_tls(td,
	    PURECAP_KERNEL_USER_CAP_UNBOUND(param->tls_base)));
}

int
freebsd64_thr_new(struct thread *td, struct freebsd64_thr_new_args *uap)
{
	struct thr_param64 param64;
	struct rtprio rtp, *rtpp;
	int error;

	if (uap->param_size != sizeof(struct thr_param64))
		return (EINVAL);

	error = copyin(PURECAP_KERNEL_USER_CAP_OBJ(uap->param),
	    &param64, uap->param_size);
	if (error != 0)
		return (error);

	if ((void *)(uintptr_t)param64.rtp != NULL) {
		error = copyin(
		    PURECAP_KERNEL_USER_CAP(param64.rtp, sizeof(struct rtprio)),
		    &rtp, sizeof(struct rtprio));
		if (error)
			return (error);
		rtpp = &rtp;
	} else
		rtpp = NULL;
	return (thread_create(td, rtpp, freebsd64_thr_new_initthr, &param64));
}

#ifdef _KPOSIX_PRIORITY_SCHEDULING
/*
 * p1003_1b.c
 */
int
freebsd64_sched_setparam(struct thread *td,
    struct freebsd64_sched_setparam_args * uap)
{

	return (user_sched_setparam(td, uap->pid,
	    __USER_CAP_OBJ(uap->param)));
}

int
freebsd64_sched_getparam(struct thread *td,
    struct freebsd64_sched_getparam_args *uap)
{

	return (user_sched_getparam(td, uap->pid,
	    __USER_CAP_OBJ(uap->param)));
}

int
freebsd64_sched_setscheduler(struct thread *td,
    struct freebsd64_sched_setscheduler_args *uap)
{

	return (user_sched_setscheduler(td, uap->pid, uap->policy,
	    __USER_CAP_OBJ(uap->param)));
}

int
freebsd64_sched_rr_get_interval(struct thread *td,
    struct freebsd64_sched_rr_get_interval_args *uap)
{

	return (user_sched_rr_get_interval(td, uap->pid,
	    __USER_CAP_OBJ(uap->interval)));
}

#else /* !_KPOSIX_PRIORITY_SCHEDULING */
FREEBSD64_SYSCALL_NOT_PRESENT_GEN(sched_setparam)
FREEBSD64_SYSCALL_NOT_PRESENT_GEN(sched_getparam)
FREEBSD64_SYSCALL_NOT_PRESENT_GEN(sched_setscheduler)
FREEBSD64_SYSCALL_NOT_PRESENT_GEN(sched_rr_get_interval)
#endif /* !_KPOSIX_PRIORITY_SCHEDULING */

/*
 * subr_profil.c
 */

int
freebsd64_profil(struct thread *td, struct freebsd64_profil_args *uap)
{

	return (kern_profil(td, __USER_CAP(uap->samples, uap->size), uap->size,
	    uap->offset, uap->scale));
}

/*
 * vm/swap_pager.c
 */

int
freebsd64_swapon(struct thread *td, struct freebsd64_swapon_args *uap)
{

	return (kern_swapon(td, __USER_CAP_STR(uap->name)));
}

int
freebsd64_swapoff(struct thread *td, struct freebsd64_swapoff_args *uap)
{

	return (kern_swapoff(td, __USER_CAP_STR(uap->name)));
}

/*
 * sys_capability.c
 */
#ifdef CAPABILITIES
int
freebsd64_cap_getmode(struct thread *td, struct freebsd64_cap_getmode_args *uap)
{

	return (kern_cap_getmode(td, __USER_CAP_OBJ(uap->modep)));
}

int
freebsd64_cap_rights_limit(struct thread *td,
   struct freebsd64_cap_rights_limit_args *uap)
{

	return (user_cap_rights_limit(td, uap->fd,
	    __USER_CAP_UNBOUND(uap->rightsp)));
}

int
freebsd64___cap_rights_get(struct thread *td,
    struct freebsd64___cap_rights_get_args *uap)
{

	return (kern_cap_rights_get(td, uap->version, uap->fd,
	    __USER_CAP_UNBOUND(uap->rightsp)));
}

int
freebsd64_cap_ioctls_limit(struct thread *td,
    struct freebsd64_cap_ioctls_limit_args *uap)
{

	return (user_cap_ioctls_limit(td, uap->fd,
	    __USER_CAP_ARRAY(uap->cmds, uap->ncmds), uap->ncmds));
}

int
freebsd64_cap_ioctls_get(struct thread *td,
    struct freebsd64_cap_ioctls_get_args *uap)
{

	return (kern_cap_ioctls_get(td, uap->fd,
	    __USER_CAP_ARRAY(uap->cmds, uap->maxcmds), uap->maxcmds));
}

int
freebsd64_cap_fcntls_get(struct thread *td,
   struct freebsd64_cap_fcntls_get_args *uap)
{

	return (kern_cap_fcntls_get(td, uap->fd,
	    __USER_CAP_OBJ(uap->fcntlrightsp)));
}
#else /* !CAPABILITIES */
int
freebsd64_cap_getmode(struct thread *td, struct freebsd64_cap_getmode_args *uap)
{

	return (ENOSYS);
}

int
freebsd64_cap_rights_limit(struct thread *td,
   struct freebsd64_cap_rights_limit_args *uap)
{

	return (ENOSYS);
}

int
freebsd64___cap_rights_get(struct thread *td,
    struct freebsd64___cap_rights_get_args *uap)
{

	return (ENOSYS);
}

int
freebsd64_cap_ioctls_limit(struct thread *td,
    struct freebsd64_cap_ioctls_limit_args *uap)
{

	return (ENOSYS);
}

int
freebsd64_cap_ioctls_get(struct thread *td,
    struct freebsd64_cap_ioctls_get_args *uap)
{

	return (ENOSYS);
}

int
freebsd64_cap_fcntls_get(struct thread *td,
   struct freebsd64_cap_fcntls_get_args *uap)
{

	return (ENOSYS);
}
#endif /* !CAPABILITIES */

/*
 * sys_getrandom.c
 */
int
freebsd64_getrandom(struct thread *td, struct freebsd64_getrandom_args *uap)
{

	return (kern_getrandom(td, __USER_CAP(uap->buf, uap->buflen),
	    uap->buflen, uap->flags));
}

/*
 * sys_pipe.c
 */
int
freebsd64_pipe2(struct thread *td, struct freebsd64_pipe2_args *uap)
{

	return (kern_pipe2(td, __USER_CAP_ARRAY(uap->fildes, 2), uap->flags));
}

/*
 * sys_procdesc.c
 */

int
freebsd64_pdgetpid(struct thread *td, struct freebsd64_pdgetpid_args *uap)
{

	return (user_pdgetpid(td, uap->fd, __USER_CAP_OBJ(uap->pidp)));
}
// CHERI CHANGES START
// {
//   "updated": 20190528,
//   "target_type": "kernel",
//   "changes_purecap": [
//     "user_capabilities"
//   ],
//   "change_comment": "struct kevent64, upstreamable"
// }
// CHERI CHANGES END
