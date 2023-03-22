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
1. philo_thread
	1. pthread_create(philo)
		1. 引数で渡す関数でthink,eat,sleepをループ
	1. pthread_create(monitor)
	1. pthread_join(philo)
	1. pthread_join(monitor)
	1. pthread_mutex_destroy
		- pthread_mutex_destroy関数は、通常はエラーを返さないことが期待されますが、ミューテックスをロックしている場合にはEBUSYエラーを返すことがあるため、エラー処理を行うことが望ましいです。
		- また、pthread_mutex_t型のミューテックスが初期化されていない場合や、すでに破棄されている場合にも未定義の動作が発生する可能性があるため、エラー処理を行うことが重要です。

- stopやnum_eatenを参照するときはpthread_mutex_tの変数をlockしてから参照する
	- done
- philoが1人の時の処理
	- done
- destoy
	- done
- error
	- data raceが起きている
		- 原因はおそらくmonitorで競合してる
		- done
	- monitorでdeathを確認した後にもまだmutexがlockしていてdestroyできていない
		- done
	- must_eat_numが与えられなかったときにdata->philo[i].num_eatenが-1以上になってそのまま処理が終了してしまう
		- dataの構造体にmust_eat_numが引数で渡されたかどうかをもつflagを作って条件式に入れる(bool is_must_eat_num)
		- done