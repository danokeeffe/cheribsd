/*
 * System call argument map.
 *
 * DO NOT EDIT-- this file is automatically generated.
 * $FreeBSD$
 */

#ifndef _CHERIABI_SYSARGMAP_H_
#define	_CHERIABI_SYSARGMAP_H_

int cheriabi_sysargmask[] = {
 [CHERIABI_SYS_exit] = (0x0),
 [CHERIABI_SYS_cheriabi_read] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_write] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_open] = (0x0 | 0x1),
 [CHERIABI_SYS_close] = (0x0),
 [CHERIABI_SYS_cheriabi_wait4] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_link] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_unlink] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_chdir] = (0x0 | 0x1),
 [CHERIABI_SYS_fchdir] = (0x0),
 [CHERIABI_SYS_cheriabi_chmod] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_chown] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_mount] = (0x0 | 0x1 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_unmount] = (0x0 | 0x1),
 [CHERIABI_SYS_setuid] = (0x0),
 [CHERIABI_SYS_cheriabi_ptrace] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_recvmsg] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_sendmsg] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_recvfrom] = (0x0 | 0x2 | 0x10 | 0x20),
 [CHERIABI_SYS_cheriabi_accept] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_getpeername] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_getsockname] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_access] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_chflags] = (0x0 | 0x1),
 [CHERIABI_SYS_fchflags] = (0x0),
 [CHERIABI_SYS_kill] = (0x0),
 [CHERIABI_SYS_dup] = (0x0),
 [CHERIABI_SYS_cheriabi_profil] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_ktrace] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getlogin] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setlogin] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_acct] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sigaltstack] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_ioctl] = (0x0 | 0x4),
 [CHERIABI_SYS_reboot] = (0x0),
 [CHERIABI_SYS_cheriabi_revoke] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_symlink] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_readlink] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_execve] = (0x0 | 0x1 | 0x2 | 0x4),
 [CHERIABI_SYS_umask] = (0x0),
 [CHERIABI_SYS_cheriabi_chroot] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_msync] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_munmap] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_mprotect] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_madvise] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_mincore] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_getgroups] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_setgroups] = (0x0 | 0x2),
 [CHERIABI_SYS_setpgid] = (0x0),
 [CHERIABI_SYS_cheriabi_setitimer] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_swapon] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getitimer] = (0x0 | 0x2),
 [CHERIABI_SYS_dup2] = (0x0),
 [CHERIABI_SYS_cheriabi_fcntl] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_select] = (0x0 | 0x2 | 0x4 | 0x8 | 0x10),
 [CHERIABI_SYS_fsync] = (0x0),
 [CHERIABI_SYS_setpriority] = (0x0),
 [CHERIABI_SYS_socket] = (0x0),
 [CHERIABI_SYS_cheriabi_connect] = (0x0 | 0x2),
 [CHERIABI_SYS_getpriority] = (0x0),
 [CHERIABI_SYS_cheriabi_bind] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_setsockopt] = (0x0 | 0x8),
 [CHERIABI_SYS_listen] = (0x0),
 [CHERIABI_SYS_cheriabi_gettimeofday] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_getrusage] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_getsockopt] = (0x0 | 0x8 | 0x10),
 [CHERIABI_SYS_cheriabi_readv] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_writev] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_settimeofday] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_fchown] = (0x0),
 [CHERIABI_SYS_fchmod] = (0x0),
 [CHERIABI_SYS_setreuid] = (0x0),
 [CHERIABI_SYS_setregid] = (0x0),
 [CHERIABI_SYS_cheriabi_rename] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_flock] = (0x0),
 [CHERIABI_SYS_cheriabi_mkfifo] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sendto] = (0x0 | 0x2 | 0x10),
 [CHERIABI_SYS_shutdown] = (0x0),
 [CHERIABI_SYS_cheriabi_socketpair] = (0x0 | 0x8),
 [CHERIABI_SYS_cheriabi_mkdir] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_rmdir] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_utimes] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_adjtime] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_quotactl] = (0x0 | 0x1 | 0x8),
 [CHERIABI_SYS_cheriabi_nlm_syscall] = (0x0 | 0x8),
 [CHERIABI_SYS_cheriabi_nfssvc] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_lgetfh] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_getfh] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_sysarch] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_rtprio] = (0x0 | 0x4),
 [CHERIABI_SYS_setfib] = (0x0),
 [CHERIABI_SYS_cheriabi_ntp_adjtime] = (0x0 | 0x1),
 [CHERIABI_SYS_setgid] = (0x0),
 [CHERIABI_SYS_setegid] = (0x0),
 [CHERIABI_SYS_seteuid] = (0x0),
 [CHERIABI_SYS_cheriabi_pathconf] = (0x0 | 0x1),
 [CHERIABI_SYS_fpathconf] = (0x0),
 [CHERIABI_SYS_getrlimit] = (0x0 | 0x2),
 [CHERIABI_SYS_setrlimit] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi___sysctl] = (0x0 | 0x1 | 0x4 | 0x8 | 0x10),
 [CHERIABI_SYS_cheriabi_mlock] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_munlock] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_undelete] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_futimes] = (0x0 | 0x2),
 [CHERIABI_SYS_getpgid] = (0x0),
 [CHERIABI_SYS_cheriabi_poll] = (0x0 | 0x1),
 [CHERIABI_SYS_semget] = (0x0),
 [CHERIABI_SYS_cheriabi_semop] = (0x0 | 0x2),
 [CHERIABI_SYS_msgget] = (0x0),
 [CHERIABI_SYS_cheriabi_msgsnd] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_msgrcv] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_shmat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_shmdt] = (0x0 | 0x1),
 [CHERIABI_SYS_shmget] = (0x0),
 [CHERIABI_SYS_cheriabi_clock_gettime] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_clock_settime] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_clock_getres] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_ktimer_create] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_ktimer_delete] = (0x0),
 [CHERIABI_SYS_cheriabi_ktimer_settime] = (0x0 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_ktimer_gettime] = (0x0 | 0x2),
 [CHERIABI_SYS_ktimer_getoverrun] = (0x0),
 [CHERIABI_SYS_cheriabi_nanosleep] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_ffclock_getcounter] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_ffclock_setestimate] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_ffclock_getestimate] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_clock_nanosleep] = (0x0 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_clock_getcpuclockid2] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_ntp_gettime] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_minherit] = (0x0 | 0x1),
 [CHERIABI_SYS_rfork] = (0x0),
 [CHERIABI_SYS_cheriabi_lchown] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_aio_read] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_aio_write] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_lio_listio] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_kbounce] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_lchmod] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_lutimes] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_preadv] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_pwritev] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_fhopen] = (0x0 | 0x1),
 [CHERIABI_SYS_modnext] = (0x0),
 [CHERIABI_SYS_cheriabi_modstat] = (0x0 | 0x2),
 [CHERIABI_SYS_modfnext] = (0x0),
 [CHERIABI_SYS_cheriabi_modfind] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_kldload] = (0x0 | 0x1),
 [CHERIABI_SYS_kldunload] = (0x0),
 [CHERIABI_SYS_cheriabi_kldfind] = (0x0 | 0x1),
 [CHERIABI_SYS_kldnext] = (0x0),
 [CHERIABI_SYS_cheriabi_kldstat] = (0x0 | 0x2),
 [CHERIABI_SYS_kldfirstmod] = (0x0),
 [CHERIABI_SYS_getsid] = (0x0),
 [CHERIABI_SYS_setresuid] = (0x0),
 [CHERIABI_SYS_setresgid] = (0x0),
 [CHERIABI_SYS_cheriabi_aio_return] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_aio_suspend] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_aio_cancel] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_aio_error] = (0x0 | 0x1),
 [CHERIABI_SYS_mlockall] = (0x0),
 [CHERIABI_SYS_cheriabi___getcwd] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sched_setparam] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_sched_getparam] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_sched_setscheduler] = (0x0 | 0x4),
 [CHERIABI_SYS_sched_getscheduler] = (0x0),
 [CHERIABI_SYS_sched_get_priority_max] = (0x0),
 [CHERIABI_SYS_sched_get_priority_min] = (0x0),
 [CHERIABI_SYS_cheriabi_sched_rr_get_interval] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_utrace] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_kldsym] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_jail] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_nnpfs_syscall] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_sigprocmask] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_sigsuspend] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sigpending] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sigtimedwait] = (0x0 | 0x1 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_sigwaitinfo] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi___acl_get_file] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_set_file] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_get_fd] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_set_fd] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_delete_file] = (0x0 | 0x1),
 [CHERIABI_SYS___acl_delete_fd] = (0x0),
 [CHERIABI_SYS_cheriabi___acl_aclcheck_file] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_aclcheck_fd] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_extattrctl] = (0x0 | 0x1 | 0x4 | 0x10),
 [CHERIABI_SYS_cheriabi_extattr_set_file] = (0x0 | 0x1 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_get_file] = (0x0 | 0x1 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_delete_file] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_aio_waitcomplete] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_getresuid] = (0x0 | 0x1 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_getresgid] = (0x0 | 0x1 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_extattr_set_fd] = (0x0 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_get_fd] = (0x0 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_delete_fd] = (0x0 | 0x4),
 [CHERIABI_SYS___setugid] = (0x0),
 [CHERIABI_SYS_cheriabi_eaccess] = (0x0 | 0x1),
 [CHERIABI_SYS_afs3_syscall] = (0x0),
 [CHERIABI_SYS_cheriabi_nmount] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___mac_get_proc] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___mac_set_proc] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___mac_get_fd] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi___mac_get_file] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi___mac_set_fd] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi___mac_set_file] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_kenv] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_lchflags] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_uuidgen] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sendfile] = (0x0 | 0x10 | 0x20),
 [CHERIABI_SYS_cheriabi_mac_syscall] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_ksem_close] = (0x0),
 [CHERIABI_SYS_ksem_post] = (0x0),
 [CHERIABI_SYS_ksem_wait] = (0x0),
 [CHERIABI_SYS_ksem_trywait] = (0x0),
 [CHERIABI_SYS_cheriabi_ksem_init] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_ksem_open] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_ksem_unlink] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_ksem_getvalue] = (0x0 | 0x2),
 [CHERIABI_SYS_ksem_destroy] = (0x0),
 [CHERIABI_SYS_cheriabi___mac_get_pid] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi___mac_get_link] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi___mac_set_link] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_extattr_set_link] = (0x0 | 0x1 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_get_link] = (0x0 | 0x1 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_extattr_delete_link] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___mac_execve] = (0x0 | 0x1 | 0x2 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_sigaction] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_sigreturn] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getcontext] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setcontext] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_swapcontext] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_swapoff] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___acl_get_link] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_set_link] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi___acl_delete_link] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___acl_aclcheck_link] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_sigwait] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_thr_create] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_thr_exit] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_thr_self] = (0x0 | 0x1),
 [CHERIABI_SYS_thr_kill] = (0x0),
 [CHERIABI_SYS_jail_attach] = (0x0),
 [CHERIABI_SYS_cheriabi_extattr_list_fd] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_extattr_list_file] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_extattr_list_link] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_ksem_timedwait] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_thr_suspend] = (0x0 | 0x1),
 [CHERIABI_SYS_thr_wake] = (0x0),
 [CHERIABI_SYS_kldunloadf] = (0x0),
 [CHERIABI_SYS_cheriabi_audit] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_auditon] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_getauid] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setauid] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getaudit] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setaudit] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getaudit_addr] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setaudit_addr] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_auditctl] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi__umtx_op] = (0x0 | 0x1 | 0x8 | 0x10),
 [CHERIABI_SYS_cheriabi_thr_new] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_sigqueue] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_kmq_open] = (0x0 | 0x1 | 0x8),
 [CHERIABI_SYS_cheriabi_kmq_setattr] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_kmq_timedreceive] = (0x0 | 0x2 | 0x8 | 0x10),
 [CHERIABI_SYS_cheriabi_kmq_timedsend] = (0x0 | 0x2 | 0x10),
 [CHERIABI_SYS_cheriabi_kmq_notify] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_kmq_unlink] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_abort2] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_thr_set_name] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_aio_fsync] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_rtprio_thread] = (0x0 | 0x4),
 [CHERIABI_SYS_sctp_peeloff] = (0x0),
 [CHERIABI_SYS_cheriabi_sctp_generic_sendmsg] = (0x0 | 0x2 | 0x8 | 0x20),
 [CHERIABI_SYS_cheriabi_sctp_generic_sendmsg_iov] = (0x0 | 0x2 | 0x8 | 0x20),
 [CHERIABI_SYS_cheriabi_sctp_generic_recvmsg] = (0x0 | 0x2 | 0x8 | 0x10 | 0x20 | 0x40),
 [CHERIABI_SYS_cheriabi_pread] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_pwrite] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_mmap] = (0x0 | 0x1),
 [CHERIABI_SYS_lseek] = (0x0),
 [CHERIABI_SYS_cheriabi_truncate] = (0x0 | 0x1),
 [CHERIABI_SYS_ftruncate] = (0x0),
 [CHERIABI_SYS_thr_kill2] = (0x0),
 [CHERIABI_SYS_cheriabi_shm_open] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_shm_unlink] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_cpuset] = (0x0 | 0x1),
 [CHERIABI_SYS_cpuset_setid] = (0x0),
 [CHERIABI_SYS_cheriabi_cpuset_getid] = (0x0 | 0x8),
 [CHERIABI_SYS_cheriabi_cpuset_getaffinity] = (0x0 | 0x10),
 [CHERIABI_SYS_cheriabi_cpuset_setaffinity] = (0x0 | 0x10),
 [CHERIABI_SYS_cheriabi_faccessat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_fchmodat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_fchownat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_fexecve] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_futimesat] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_linkat] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_mkdirat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_mkfifoat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_openat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_readlinkat] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_renameat] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_symlinkat] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_unlinkat] = (0x0 | 0x2),
 [CHERIABI_SYS_posix_openpt] = (0x0),
 [CHERIABI_SYS_cheriabi_gssd_syscall] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_jail_get] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_jail_set] = (0x0 | 0x1),
 [CHERIABI_SYS_jail_remove] = (0x0),
 [CHERIABI_SYS_closefrom] = (0x0),
 [CHERIABI_SYS_cheriabi___semctl] = (0x0 | 0x8),
 [CHERIABI_SYS_cheriabi_msgctl] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_shmctl] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_lpathconf] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi___cap_rights_get] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_cap_getmode] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_pdfork] = (0x0 | 0x1),
 [CHERIABI_SYS_pdkill] = (0x0),
 [CHERIABI_SYS_cheriabi_pdgetpid] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_pselect] = (0x0 | 0x2 | 0x4 | 0x8 | 0x10 | 0x20),
 [CHERIABI_SYS_cheriabi_getloginclass] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_setloginclass] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_rctl_get_racct] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_rctl_get_rules] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_rctl_get_limits] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_rctl_add_rule] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_rctl_remove_rule] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_posix_fallocate] = (0x0),
 [CHERIABI_SYS_posix_fadvise] = (0x0),
 [CHERIABI_SYS_cheriabi_wait6] = (0x0 | 0x4 | 0x10 | 0x20),
 [CHERIABI_SYS_cheriabi_cap_rights_limit] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_cap_ioctls_limit] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_cap_ioctls_get] = (0x0 | 0x2),
 [CHERIABI_SYS_cap_fcntls_limit] = (0x0),
 [CHERIABI_SYS_cheriabi_cap_fcntls_get] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_bindat] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_connectat] = (0x0 | 0x4),
 [CHERIABI_SYS_cheriabi_chflagsat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_accept4] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_pipe2] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_aio_mlock] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_procctl] = (0x0 | 0x8),
 [CHERIABI_SYS_cheriabi_ppoll] = (0x0 | 0x1 | 0x4 | 0x8),
 [CHERIABI_SYS_cheriabi_futimens] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_utimensat] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_fdatasync] = (0x0),
 [CHERIABI_SYS_cheriabi_fstat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_fstatat] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_fhstat] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_getdirentries] = (0x0 | 0x2 | 0x8),
 [CHERIABI_SYS_cheriabi_statfs] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_fstatfs] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_getfsstat] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_fhstatfs] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_mknodat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_kevent] = (0x0 | 0x2 | 0x8 | 0x20),
 [CHERIABI_SYS_cheriabi_cpuset_getdomain] = (0x0 | 0x10 | 0x20),
 [CHERIABI_SYS_cheriabi_cpuset_setdomain] = (0x0 | 0x10),
 [CHERIABI_SYS_cheriabi_getrandom] = (0x0 | 0x1),
 [CHERIABI_SYS_cheriabi_getfhat] = (0x0 | 0x2 | 0x4),
 [CHERIABI_SYS_cheriabi_fhlink] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_fhlinkat] = (0x0 | 0x1 | 0x4),
 [CHERIABI_SYS_cheriabi_fhreadlink] = (0x0 | 0x1 | 0x2),
 [CHERIABI_SYS_cheriabi_funlinkat] = (0x0 | 0x2),
 [CHERIABI_SYS_cheriabi_copy_file_range] = (0x0 | 0x2 | 0x8),
};

#endif /* !_CHERIABI_SYSARGMAP_H_ */
