#ifndef CONFIG_H
#define CONFIG_H

//窗口大小配置
    //整个游戏窗口
#define GAME_WIDTH 1000
#define GAME_HEIGHT 618


    //弹窗大小
#define POPWIDGET_WIDTH 500
#define POPWIDGET_HEIGHT 300
    //滚动条窗口大小
#define SCROLLWIDGET_WIDTH 100
#define SCROLLWIDGET_HEIGHT 700
//游戏机制配置
    //检测拖拽中心
#define SLICECHECKCENTER 37
    //图片大小
#define SLICEWIDTH 80
#define SLICEHEIGHT 80
    //游戏模式
enum gameMode{practiceMode, competitionMode, endlessMode};
enum customDialog{inputDialog, selectModeDialog};
enum endlessDifficulty{easy = 1, difficult};//困难对应4元素缩小出现范围，中央重叠度较大，角落不会出现大块的X，但边界X会比较多，

//路径配置
    //游戏文件
#define ACCOUNTLISTROAD "accountList7.bin"
#define PRACTICEMAPROAD "practiceMap.bin"
#define COMPETITION_MAP_ROAD "competitionMap.bin"
#define USERDEFINED_RPRATICEMAP_PATH "userPracticeMapRecord.dat"
#define USERDEFINED_COMPETITIONMAP_PATH "userCompetitionMapRecord.dat"
#define ENDLESSPRACTICE_RECORD_PATH "endlessPracticeRecord.dat"
#define ENDLESSCOMPETITION_RECORD_PATH "endlessCompetitionRecord.dat"
#define PRACTICE_RECORD_PATH "practiceRecord2.dat"
#define COMPETITION_RECORD_PATH "competitionRecord3.dat"
#define TOURISTPLAYER_RECORD_PATH "touristPlayerRecord1.dat"
    //游戏资源
#define GAMENAME_PATH ":/res/GameName.png"
#define SQUARE_PATH ":/res/Square (2).png"
#define TRIANGLE_PATH ":/res/triangle (2).png"
#define CIRCLE_PATH ":/res/circle.png"
#define ERROR_PATH ":/res/叉.png"
#define LOADFAILURE_PATH ":/res/loadFailure.png"
#define SLICETOPUT1 ":/res/sliceToPut1.png"
#define SLICETOPUT2 ":/res/slicetoPut2.png"
#define SLICETOPUT3 ":/res/sliceToPut3.png"
#define SLICETOPUT4 ":/res/sliceToPut4.png"
#define HIDETARGETSLICE_PATH ":/res/hideSlice.jpg"
#define BACKGROUND_PATH ":/res/background4.png"
#define ENDLESSBTN_PATH ":/res/endlessBtn.png"




#endif // CONFIG_H
