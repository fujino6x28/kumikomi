
// enum型の変数は 値としてSTART, RUNNING, DEAD, RESTART, CLEAR のいずれかを取る。
// 実際のプログラム実行中は整数の値で表され，STARTが0，RUNNINGが1, DEADが2, ...となる。
enum state {START, RUNNING, DEAD, RESTART, CLEAR};


extern void game_step(void);             // 1ティックの動作を行なう．
extern enum state game_get_state(void);  // 今の状態を問い合わせる．
extern void game_set_state(enum state);  // 状態を変更する．
