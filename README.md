# PlaneGame

### 摘要

使用MFC完成飞机大战游戏

### 总体设计

实现的基本功能：窗口开始结束向导，游戏战机的移动，不同背景图的滚动、选择与切换，关卡的转换，各个功能键的执行，重新开始窗口，Boss 的血量条的绘制，碰撞爆炸效 果，模式转换，子弹的各种飞行轨迹。 

游戏中的主要角色：主机，敌机 1（1 发子弹），敌机 2（3 发子弹），Boss1、 Boss2、 Boss3、Final Boss，爱心，主机导弹和火焰弹，敌机子弹等。 

### 详细设计

1.  界面显示功能：游戏左上角有信息展示功能，包括模式切换、Blood(血量)， Score(分数）以及 Level（等级 Num of bomb(导弹的数量)，而右上角则是飞 机大战可以实现的各种功能。
2. 方向键控制 blood > 1 战机移动来攻击或躲避敌机和 Boss，自动发射两列子弹 (当蓝条大于预设最大值（1001）的一般时按 Ctrl 发射三发火焰弹)轰炸敌机 或 Boss，同时战机会被敌机和 Boss 的子弹攻击，当战机 Blood 为零时游戏 结束，当 boos 血量为零时进入下一关。 
3. 游戏过程中，敌机出现的位置随机，速度随机，随着游戏的关卡增大，增加敌 机种类和数量。每一关战机的血量都不同。每一关都涉及有一个 boss 来增加 游戏的难度与可玩性 
4. 爆炸效果，敌机或 Boss 子弹击中战机发生爆炸，战机发射子弹击毁敌机或 Boss 以及战机和敌机发生碰撞时产生爆炸。爆炸后敌机 1 和敌机 2 消失，Boss 生 命值减少，战机生命值减少。 
5. 功能键简介：P 键暂停，C 键继续，O 键切换无敌模式，Z 键切换普通模式，， Ctrl 键发射三发子弹，方向键移动 
6. 游戏附加功能： 
   1. 游戏界面滚动效果，以及游戏战机、敌机的透明贴图。 
   2. 开始窗口及关卡弹窗等弹窗效果。 
   3. 游戏中增加了游戏道具，增强了可玩性。战机与爱心碰撞可以加血量，血量上 4 限为为当前关卡飞机的血量上限. 
   4. 每一关设计一个 Boss，击败 Boss 才可以进入下一关。 
   5. 随着关卡的增大，敌机数量和种类改变，增加高关卡难度。 
   6. 增加子弹的飞行轨迹，包括延 Y 轴方向、Y=2X、Y=1/2X、Y=-2X、Y=-1/2X 共四个方向，同时设置某些子弹碰到边界反弹

