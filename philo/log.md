# philosophers

## flow
1. check_args
	1. argcが5or6
	1. argvがdigit
	1. philo_numが2人以上200人未満
	1. time_to_die,time_to_eat,time_to_sleepが1以上,must_eat_numがある場合は1以上
1. init_philo
	1. run_mutex
		1. pthread_mutex_init(&fork)
	1. philo_numまでループ
	1. forkの割り当て
1. create_thread
	1. pthread_create(philo)
		1. 引数で渡す関数でthink,eat,sleepをループ
	1. pthread_create(monitor)
	1. pthread_join(philo)
	1. pthread_join(monitor)
	1. pthread_mutex_destroy

- stopやnum_eatenを参照するときはpthread_mutex_tの変数をlockしてから参照する
- philoが1人の時の処理
- destoy