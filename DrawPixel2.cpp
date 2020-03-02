#include "DxLib.h" 
#include "stdlib.h"
#include <stdio.h>
#include <math.h>
#include <conio.h>//セーブデータで使用するらしい...
#define PI 3.1415926f
int sutezinosaidaiti = 1;//選べるステージの最大値。
int genzainosutezi = 0;//選んだステージの面。0は選んでない状態
int sutezinogimikku = 0;//ステージ上の仕掛けとかに使う。一度だけ敵の出現を作動させたりするのに使う。


//int kabeS[3][2][2];//空中物の位置。[][][]の二つ目が0でx、1でy座標。三つ目が0で左/上端、1で右/下端。
double kabeL[100][2][2];//地上物の位置。[][][]の二つ目が0でx、1でy座標。三つ目が0で左/上端、1で右/下端。
int k = 14;//壁の個数k個ある。
int i;//壁の繰り返し用の変数。
double kabeD[50][2][2];//ダメージ用の壁の位置。kabeLと同じ。[][][]の二つ目が0でx、1でy座標。三つ目が0で左/上端、1で右/下端。
int kabeDidou1 = 0;//ダメージ用の壁の移動用変数。
int kabeDidou[8] = {0,0,0,0,0,0,0,0};//回るダメージ壁用の変数。[6]は、繰り返し用の変数。
//int kabeDidou2 = 0;//追いかけるダメージ壁の変数。
//int kabeDidou2sin = 0;
//int kabeDidou2cos = 0;
int damezikabenokougekiryoku = 10;//ダメージ壁の攻撃力。ここで調整する。変数名に「-」は使えない。ダメジ...
int n = 16;//ダメージ壁の個数n個ある。
int m = 0;//ダメージ壁の繰り返し用の変数
int kuroikabenokazu = 30;//黒い壁の数。
double kuroikabe[50][2][2];//黒い壁用の壁の位置。kabeLと同じ。[][][]の二つ目が0でx、1でy座標。三つ目が0で左/上端、1で右/下端。触れると体力を0にする。
double tannikabe[20][2][2];//集めるための単位。[][][]の二つ目が0でx、1でy座標。三つ目が0で左/上端、1で右/下端。
int tanninokazu = 6;//単位の数。
int genzainotanninokazu = 0;//現在の単位の数。
int tannihituyousuu=6;//単位必要数。この変数の数だけ単位を集めるとクリア。
int p=0;//集める壁の繰り返し用の変数。
int kaihukuaitemunokazu = 10;//回復アイテムの数。
double kaihukuaitemu[50][4];/* =//0X座標 1Y座標 2回復量 3存在するかどうか。1で存在。0で存在しない。
{
	{ 50, 50, 50, 1,},
	{ 100, 0, 0, 0,},
	{ 200, 0, 0, 0, },
	{ 300, 0, 0, 0,},
	{ 400, 0, 0, 0,},
	{ 500, 0, 0, 0,},
	{ 600, 0, 0, 0,},
	{ 700, 0, 0, 0,},
	{ 800, 0, 0, 0,},
	{ 900, 0, 0, 0,}, }; */
int okaneaitemunokazu = 16;//お金アイテムの数。
double okaneaitemu[50][4];/* =//0X座標 1Y座標 2お金入手量。 3存在するかどうか。1で存在。0で存在しない。
{
	{ 100, 50, 50, 1, },
	{ 100, 0, 0, 0, },
	{ 200, 0, 0, 0, },
	{ 300, 0, 0, 0, },
	{ 400, 0, 0, 0, },
	{ 500, 0, 0, 0, },
	{ 600, 0, 0, 0, },
	{ 700, 0, 0, 0, },
	{ 800, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 100, 0, 0, 0, },
	{ 900, 0, 0, 0, }, };*/
typedef struct {
	int stairyokusaidaiti;//体力の最大値。最大は一応638かな。画面的に。int aaa = 1;のように書くとエラーが出るので注意。自分はこれで死にました.........だって関係の無いところにエラーが出るんだもん。。。
	//int stairyoku = 100;//自機の体力。
	//int stairyokuzenkai = 100;//前回の体力。効果音を鳴らすときに使う。
	int skougekiryoku;// = 10;//自機の攻撃力。
	double stamasokudo;//弾の速度。レベルアップ有り。20かな。最大値は。
	int sokane;// = 1000000;//現在のお金の金額。
	int sokanenosaidaiti;// = 1000000;//お金の最大値。
	double ssokudo;//移動速度最大は10かも。//tairyokusaidaiti,tairyoku,tairyokuzenkai,kougekiryoku,tamasokudo,okane,okanenosaidaiti,sokudo
	int ssutezinosaidaiti;
}SaveData_t;

	
//typedef struct {
int tairyokusaidaiti=100;//体力の最大値。最大は一応638かな。画面的に。
int tairyoku = 100;//自機の体力。
int tairyokuzenkai = 100;//前回の体力。効果音を鳴らすときに使う。
int kougekiryoku = 10;//自機の攻撃力。
double tamasokudo = 4;//弾の速度。レベルアップ有り。20かな。最大値は。
int okane = 1000000;//現在のお金の金額。
int okanenosaidaiti = 1000000;//お金の最大値。
double sokudo = 1;//移動速度最大は10かも。
				  //tairyokusaidaiti,tairyoku,tairyokuzenkai,kougekiryoku,tamasokudo,okane,okanenosaidaiti,sokudo
//}SaveData_t;
int muteki = 100;//ダメージをくらった後の、無敵時間。
int sentakujoutai = 0;//メニュー画面でマウスで選んだら1にして選んでなかったら0にする。1にするときに音を鳴らす。
int sentakujoutaizenkai = 0;//前回の選択状態の変数。
double tama[50][7];//0=X,1=Y,2=sin,3=cos,4=ラジアン,5=特になし,6=存在するなら1、存在しないなら0に対応している。通常弾。
double tametama[26][7];//0=X,1=Y,2=sin,3=cos,4=ラジアン,5=特になし,6=存在するなら1、存在しないなら0に対応している。溜め弾。25弾ある。
int tamazikan = 51;//弾を出しているときの時間。弾間隔×弾数までを繰り返し、0になる。1カウントで1増加する。
int tametamazikan1 = 100;//1段階目溜め弾を出しているときの時間。50カウントで無くなる。
int tametamazikan2 = 100;//2段階目溜め弾を出しているときの時間。50カウントで無くなる。
int mausux=0;//マウスのX座標
int mausuy=0;//マウスのY座標
int kurikaesi=0;//繰り返し用の変数。自由に使っていいと思う。
int tamakankaku=5;//弾を打つ間隔。レベルアップ有り。の予定だったが、5で固定しそう。
int tamakazu=50;//弾の最大個数。多くしておけばオーケー。
int tamahikyori = 50;//弾の飛距離というか、存在する時間。50で固定しそう。(溜め弾の関係上。)
int mausukaiten = 99;//マウスの回転量を調べる。
int mausuhidari = 0;
int mausuhidarizenkai = 0;//マウスの左の1つ前の状態を確認する。
int mausumigi = 0;
int mausumigizenkai = 0;//マウスの右の1つ前の状態を確認する。
int mausuhidariutu = 0;//チャージ弾を打っているかどうかを確認する。
int mausumannnaka = 0;
double memo[50][3] = {//ステージ上に表示するメモ。0X 1Y 2表示するかどうか、存在するなら1、存在しないなら0に対応している。
	{0,0,1},{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
	{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
	{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
	{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },
	{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 },{ 0,0,1 }, };
int memonokazu = 50;//メモの数を一応変えられるようにした。
int zakotekinokazu = 0;//ザコ敵の数。zakoteki[]←と同じ数にしなければいけない。(それより多い数だと、撃つ敵の変数がザコ敵に変わってしまう。)
double zakoteki[100][12];/* = {//0X座標 1Y座標 2ラジアンの値 3スピードを調整するための時間 4実際のスピード 5体力 6体力の色 7体当たりの攻撃力 8倒したとき入手できるお金の金額 9方向転換にかかる時間 10加速度 11角度のずれの値*100
	//※体力は、0以下で-10000にしてお金を足して、-10000で完全になくなる。
{100, 0, 0, 0, 0, 200 ,0,10,100,50,0.1,500}, 
{200, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{300, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{400, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{500, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{600, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{700, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{ 100, 0, 0, 0, 0, 200 ,0,10,100,50,0.1,500 },
{ 200, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 300, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 400, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 500, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 600, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 700, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 100, 0, 0, 0, 0, 200 ,0,10,100,50,0.1,500 },
{ 200, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 300, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 400, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 500, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 600, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 700, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{800, 0, 0, 0, 0, 0 ,0,10,10,100,1,5},
{ 200, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 300, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 400, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 500, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 600, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 700, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{ 800, 0, 0, 0, 0, 0 ,0,10,10,100,1,5 },
{900, 0, 0, 0, 0, 0 ,0,10,10,100,1,5}, };*/
int ututekinokazu = 10;//撃つ敵の数。
double ututeki[100][19];/* = {//0X座標 1Y座標 2ラジアンの値 3弾を撃つ間隔 4弾が存在するかどうか0で存在しない1で存在する 5体力 6体力の色 7弾のX座標 8弾のY座標  9弾のラジアン 10倒したとき入手できるお金の金額 11体当たりの攻撃力 12動くスピード 13近づき始める距離 14離れ始める距離 15撃つ敵の弾の攻撃力 16撃つ敵の弾のスピード 17撃つ敵の弾の撃つ間隔の時間の実際の時間 18角度のずれの値*100の値
	{ 0,0,0,300,1,1000,0,0,0,0,50,10,1,50000,10000,10,5,0,500 },
	{ 100, 0, 0, 100, 0, 100,0,0,0 ,0,0,10,1,50000,10000,10,3,0,1 },
	{ 200, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,1 },
	{ 300, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 400, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 500, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 600, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 100, 0, 0, 100, 0, 100,0,0,0 ,0,0,10,1,50000,10000,10,3,0,1 },
	{ 200, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,1 },
	{ 300, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 400, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 500, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 600, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 700, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 800, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 200, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,1 },
	{ 300, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 400, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 500, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 600, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 700, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 800, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 200, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,1 },
	{ 300, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 400, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 500, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 600, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 700, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 800, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 },
	{ 900, 0, 0, 0, 0, 0,0,0,0 ,0,0,10,2,50000,10000,10,3,300,5 }, };*/
int utimakurutekinokazu = 2;//撃ちまくる敵の数。
double utimakuruteki[32][29];/* = {//0X座標 1Y座標 2ラジアンの値 3弾を撃つ間隔 4弾1が存在するかどうか0で存在しない1で存在する 5体力 6体力の色 7弾1のX座標 8弾1のY座標  9弾のラジアン 10倒したとき入手できるお金の金額 11体当たりの攻撃力 12弾2のX座標 13弾2のY座標 14撃つ弾の角度の間隔 15撃つ敵の弾の攻撃力 16撃つ敵の弾のスピード 17撃つ敵の弾の撃つ間隔の時間の実際の時間 18弾3のX 19弾3のY 20弾4のX 21弾4のY 22弾5のX 23弾5のY 24弾2の存在 25弾3の存在 26弾4の存在 27弾5の存在 28角度のずれの値*100の値
	{     300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 300,400,0,200,1,1000,0,0,0,0,100,10,0,0,20,10,2,0,0,0,0,0,0,0,0,0,0,0,500 },
	{ 400, 400, 0, 200, 0, 100,0,0,0 ,0,100,10,0,0,15,10,2,0,0,0,0,0,0,0,0,0,0,0,500 }, };*/
int genzainozikan = 0;//ステージを開始し始めた時からの時間。
int dekaitekinokazu = 9;//デカい敵の数。dekaiteki[]←と同じ数にしなければいけない。(それより多い数だと、撃つ敵の変数がザコ敵に変わってしまう。)
double dekaiteki[100][9];// = {//0X座標 1Y座標 2未使用 3未使用 4未使用 5体力 6体力の色 7体当たりの攻撃力 8倒したとき入手できるお金の金額 
						  //※体力は、0以下で-10000にしてお金を足して、-10000で完全になくなる。
	/*{ 100, 0, 0, 0, 0, -10000 ,0,10,100 },
	{ 200, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 300, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 400, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 500, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 600, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 700, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 100, 0, 0, 0, 0, -10000 ,0,10,100 },
	{ 200, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 300, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 400, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 500, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 600, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 700, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 800, 0, 0, 0, 0, -10000 ,0,10,10 },
	{ 900, 0, 0, 0, 0, -10000 ,0,10,10 }, };
	*/
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetOutApplicationLogValidFlag(FALSE);
	SetMainWindowText("解りにくいだけ");
	ChangeWindowMode(TRUE);
	SetDrawScreen(DX_SCREEN_BACK);
	DxLib_Init();
	//画像ゾーン
	int touhu = LoadGraph("画像/touhu.jpg", false);
	int touhumagao = LoadGraph("画像/touhumagao.jpg", false);
	int touhunaku = LoadGraph("画像/touhunaku.jpg", false);
	int touhusuppai = LoadGraph("画像/touhusuppai.jpg", false);
	int touhuhunbari= LoadGraph("画像/touhuhunbari.jpg", false);
	int tamagazou = LoadGraph("画像/tama.jpg", false);
	//int haikei = LoadGraph("画像/背景.png", false);
	int bannou = LoadGraph("画像/山本さん.png", false);
	int bannou2 = LoadGraph("画像/ダメージ.png", false);
	int zakotekinogazou = LoadGraph("画像/zakoteki.png", true);
	int ututekinogazou = LoadGraph("画像/ututeki.png", true);
	int ututekinotamanogazou = LoadGraph("画像/tekinotama.jpg", true);
	int utimakurutekinogazou= LoadGraph("画像/utimakuruteki.png", true);
	int aoigazou = LoadGraph("画像/aoigazou.jpg", true);//撃ちまくる敵の弾
	int dekaitekinogazou = LoadGraph("画像/dekaiteki.png", true);
	int kuroigazou = LoadGraph("画像/kurogazou.jpg", true);
	//int bosuteki = LoadGraph("画像/bosuteki.png", true);
	

	int kaihukuaitemugazou= LoadGraph("画像/kaihukuaitemu.jpg", false);
	int okaneaitemugazou= LoadGraph("画像/okaneaitemu.jpg", true);
	int tannigazou= LoadGraph("画像/tanni.png", true);
	//ここからメニュー画面関連の画像
	int sutezi1nogazou = LoadGraph("画像/01.png", true);
	int sutezi2nogazou = LoadGraph("画像/02.png", true);
	int sutezi3nogazou = LoadGraph("画像/03.png", true);
	int sutezi4nogazou = LoadGraph("画像/04.png", true);
	int sutezi5nogazou = LoadGraph("画像/05.png", true);
	int sutezi6nogazou = LoadGraph("画像/06.png", true);
	int sutezi7nogazou = LoadGraph("画像/07.png", true);
	int sutezi8nogazou = LoadGraph("画像/08.png", true);
	int sutezi9nogazou = LoadGraph("画像/09.png", true);
	int sutezi10nogazou = LoadGraph("画像/10.png", true);
	int sutezi11nogazou = LoadGraph("画像/11.png", true);
	int sutezi12nogazou = LoadGraph("画像/12.png", true);
	int sutezi13nogazou = LoadGraph("画像/13.png", true);
	int sutezi14nogazou = LoadGraph("画像/14.png", true);
	int sutezi15nogazou = LoadGraph("画像/15.png", true);
	int sutezi16nogazou = LoadGraph("画像/16.png", true);
	int sutezi17nogazou = LoadGraph("画像/17.png", true);
	int sutezi18nogazou = LoadGraph("画像/18.png", true);
	int sutezi19nogazou = LoadGraph("画像/19.png", true);
	int sutezi20nogazou = LoadGraph("画像/20.png", true);
	int pureizikannnogazou=LoadGraph("画像/pureizikan.png", true);
	int sebunogazou = LoadGraph("画像/se-bu.png", true);
	int sebusimasitanogazou = LoadGraph("画像/se-busimasita.png", true);
	int asobikatanogazou = LoadGraph("画像/asobikata.png", true);
	int setteinogazou = LoadGraph("画像/settei.png", true);
	int lifenogazou = LoadGraph("画像/life.jpg", true);
	int powernogazou = LoadGraph("画像/power.jpg", true);
	int speednogazou = LoadGraph("画像/speed.jpg", true);
	int rangenogazou = LoadGraph("画像/range.jpg", true);
	int huriwakeyarinaosinogazou = LoadGraph("画像/huriwakeyarinaosi.png", true);
	int tyekkuhaikei = LoadGraph("画像/tyekkuhaikei.png", true);
	//画像ゾーン
	//音声ゾーン
	int ongakumenyu = LoadSoundMem("音声/game_maoudamashii_5_town26.mp3"); //メニュー画面の音楽   
	ChangeVolumeSoundMem(255 * 70 / 100, ongakumenyu);//音の大きさを半分にしている。
	int ongakusentou = LoadSoundMem("音声/bgm_maoudamashii_cyber19.mp3"); //戦闘画面の音楽
	//ChangeVolumeSoundMem(255 * 50 / 100, ongakusentou);//音の大きさを半分にしている。
	int koukaonsentaku = LoadSoundMem("音声/se_maoudamashii_se_finger01.mp3"); //メニュー画面でマウスを合わせたときの効果音
	int koukaontekitamahassya = LoadSoundMem("音声/se_maoudamashii_system43.mp3"); //敵が弾を発射したときの効果音
	int koukaonkurikku = LoadSoundMem("音声/se_maoudamashii_se_switch02.mp3"); //メニューでクリックしたときの効果音
	int koukaonsebusitatoki = LoadSoundMem("音声/se_maoudamashii_onepoint10.mp3"); //セーブしたときの効果音
	int koukaonokanewohirottatoki = LoadSoundMem("音声/coin03.mp3"); //お金を拾ったときの効果音
    int koukaonkaihukuaitemu = LoadSoundMem("音声/powerup03.mp3"); //回復アイテムを拾ったときの効果音
	int koukaontamehazimetatoki = LoadSoundMem("音声/tamehazimetatoki.mp3"); //溜め始めたの効果音
	ChangeVolumeSoundMem(255 * 70 / 100, koukaontamehazimetatoki);//音の大きさを半分にしている。
	int koukaontame1 = LoadSoundMem("音声/tame1.mp3"); //溜め1段階の効果音
	ChangeVolumeSoundMem(255 * 70 / 100, koukaontame1);//音の大きさを半分にしている。
	int koukaontame2 = LoadSoundMem("音声/tame2.mp3"); //溜め2段階の効果音
	ChangeVolumeSoundMem(255 * 70 / 100, koukaontame2);//音の大きさを半分にしている。
	int koukaontametehassya = LoadSoundMem("音声/tametehassya.mp3"); //溜め弾発射の効果音
	ChangeVolumeSoundMem(255 * 70 / 100, koukaontametehassya);//音の大きさを半分にしている。
	int koukaonsindatoki = LoadSoundMem("音声/se_maoudamashii_battle18.mp3"); //の効果音
	int koukaontanniwohirottatoki = LoadSoundMem("音声/tanniwohirottatoki.mp3"); //の効果音
	int koukaondameziataeta = LoadSoundMem("音声/dameziataeta.mp3"); //ダメージを与えたときの効果音
	ChangeVolumeSoundMem(255 * 50 / 100, koukaondameziataeta);//音の大きさを半分にしている。
	int koukaondamezikuratta = LoadSoundMem("音声/damezikuratta.mp3"); //ダメージをくらったときの効果音
	int koukaongemuoba = LoadSoundMem("音声/gemuoba.mp3"); //ゲームオーバーのときの効果音
	ChangeVolumeSoundMem(255 * 70 / 100, koukaongemuoba);//音の大きさを半分にしている。
	//音声ゾーン
	kabeL[0][0][0] = 0;
	kabeL[0][0][1] = 670;
	kabeL[0][1][0] = 0;
	kabeL[0][1][1] = 30;
	kabeL[1][0][0] = 0;
	kabeL[1][0][1] = 30;
	kabeL[1][1][0] = 0;
	kabeL[1][1][1] = 480;
	kabeL[2][0][0] = 640;
	kabeL[2][0][1] = 670;
	kabeL[2][1][0] = -500;
	kabeL[2][1][1] = 610;
    kabeL[3][0][0] = -130;
	kabeL[3][0][1] = 670;
	kabeL[3][1][0] = 580;
	kabeL[3][1][1] = 610;
	kabeL[4][0][0] = -130;
	kabeL[4][0][1] = -100;
	kabeL[4][1][0] = -500;
	kabeL[4][1][1] = 610;
	kabeL[5][0][0] = -130;
	kabeL[5][0][1] = 670;
	kabeL[5][1][0] = -500;
	kabeL[5][1][1] = -470;
	kabeL[6][0][0] = 210;
	kabeL[6][0][1] = 260;
	kabeL[6][1][0] = -260;
	kabeL[6][1][1] = -210;
	/*kabeL[7][0][0] = -130;
	kabeL[7][0][1] = -100;
	kabeL[7][1][0] = -500;
	kabeL[7][1][1] = 580;
	kabeL[8][0][0] = -130;
	kabeL[8][0][1] = -100;
	kabeL[8][1][0] = -500;
	kabeL[8][1][1] = 580;
	kabeL[9][0][0] = -130;
	kabeL[9][0][1] = -100;
	kabeL[9][1][0] = -500;
	kabeL[9][1][1] = 580;
	kabeL[10][0][0] = -130;
	kabeL[10][0][1] = -100;
	kabeL[10][1][0] = -500;
	kabeL[10][1][1] = 580;*/
	//kabeL[11][0][0] = -130;
	//kabeL[11][0][1] = 610;
	//kabeL[11][1][0] = 0;
	//kabeL[11][1][1] = 30;
	kabeL[12][0][0] = 640;
	kabeL[12][0][1] = 670;
	kabeL[12][1][0] = -500;
	kabeL[12][1][1] = 610;
	kabeL[13][0][0] = -130;
	kabeL[13][0][1] = 670;
	kabeL[13][1][0] = 580;
	kabeL[13][1][1] = 610;
	kabeL[14][0][0] = -130;
	kabeL[14][0][1] = 670;
	kabeL[14][1][0] = -500;
	kabeL[14][1][1] = -470;
	//kabeL[15][0][0] = -130;
	//kabeL[15][0][1] = 670;
	//kabeL[15][1][0] = -500;
	//kabeL[15][1][1] = -470;
	//kabeL[16][0][0] = 640;
	//kabeL[16][0][1] = 670;
	//kabeL[16][1][0] = -500;
	//kabeL[16][1][1] = 580;
	/*kabeL[17][0][0] = -130;
	kabeL[17][0][1] = -100;
	kabeL[17][1][0] = -500;
	kabeL[17][1][1] = 580;
	kabeL[18][0][0] = -130;
	kabeL[18][0][1] = -100;
	kabeL[18][1][0] = -500;
	kabeL[18][1][1] = 580;
	kabeL[19][0][0] = -130;
	kabeL[19][0][1] = -100;
	kabeL[19][1][0] = -500;
	kabeL[19][1][1] = 580;
	kabeL[20][0][0] = 0;
	kabeL[20][0][1] = 640;
	kabeL[20][1][0] = 0;
	kabeL[20][1][1] = 30;
	kabeL[21][0][0] = 0;
	kabeL[21][0][1] = 30;
	kabeL[21][1][0] = 0;
	kabeL[21][1][1] = 480;
	kabeL[22][0][0] = 640;
	kabeL[22][0][1] = 670;
	kabeL[22][1][0] = -500;
	kabeL[22][1][1] = 610;
	kabeL[23][0][0] = -100;
	kabeL[23][0][1] = 670;
	kabeL[23][1][0] = 580;
	kabeL[23][1][1] = 610;
	kabeL[24][0][0] = -130;
	kabeL[24][0][1] = -100;
	kabeL[24][1][0] = -500;
	kabeL[24][1][1] = 580;
	kabeL[25][0][0] = -130;
	kabeL[25][0][1] = -100;
	kabeL[25][1][0] = -500;
	kabeL[25][1][1] = 580;
	kabeL[26][0][0] = -130;
	kabeL[26][0][1] = -100;
	kabeL[26][1][0] = -500;
	kabeL[26][1][1] = 580;
	kabeL[27][0][0] = -130;
	kabeL[27][0][1] = -100;
	kabeL[27][1][0] = -500;
	kabeL[27][1][1] = 580;
	kabeL[28][0][0] = -130;
	kabeL[28][0][1] = -100;
	kabeL[28][1][0] = -500;
	kabeL[28][1][1] = 580;
	kabeL[29][0][0] = -130;
	kabeL[29][0][1] = -100;
	kabeL[29][1][0] = -500;
	kabeL[29][1][1] = 580;*/	//左、右、上、下の順番。

	
	
	//ここからステージ1の緑の壁の設定。
	/*
	kabeL[0][0][0] = -30;
	kabeL[0][0][1] = 0;
	kabeL[0][1][0] = -30;
	kabeL[0][1][1] = 480;
	kabeL[1][0][0] = -30;
	kabeL[1][0][1] = 1230;
	kabeL[1][1][0] = -30;
	kabeL[1][1][1] = 0;
	kabeL[2][0][0] = -30;
	kabeL[2][0][1] = 1230;
	kabeL[2][1][0] = 480;
	kabeL[2][1][1] = 510;
	kabeL[3][0][0] = 1200;
	kabeL[3][0][1] = 1230;
	kabeL[3][1][0] = -30;
	kabeL[3][1][1] = 180;
	kabeL[4][0][0] = 1200;
	kabeL[4][0][1] = 1230;
	kabeL[4][1][0] = 300;
	kabeL[4][1][1] = 510;
	kabeL[5][0][0] = 1200;
	kabeL[5][0][1] = 1800;
	kabeL[5][1][0] = 150;
	kabeL[5][1][1] = 180;
	kabeL[6][0][0] = 1200;
	kabeL[6][0][1] = 1800;
	kabeL[6][1][0] = 300;
	kabeL[6][1][1] = 330;
	kabeL[7][0][0] = 1770;
	kabeL[7][0][1] = 1800;
	kabeL[7][1][0] = 0;
	kabeL[7][1][1] = 180;
	kabeL[8][0][0] = 1770;
	kabeL[8][0][1] = 1800;
	kabeL[8][1][0] = 300;
	kabeL[8][1][1] = 510;
	kabeL[9][0][0] = 1770;
	kabeL[9][0][1] = 1800;
	kabeL[9][1][0] = 720;
	kabeL[9][1][1] = 1230;
	kabeL[10][0][0] = 1770;
	kabeL[10][0][1] = 2400;
	kabeL[10][1][0] = -30;
	kabeL[10][1][1] = 0;
	kabeL[11][0][0] = 1770;
	kabeL[11][0][1] = 2040;
	kabeL[11][1][0] = 480;
	kabeL[11][1][1] = 510;
	kabeL[12][0][0] = 1770;
	kabeL[12][0][1] = 2040;
	kabeL[12][1][0] = 690;
	kabeL[12][1][1] = 720;
	kabeL[13][0][0] = 1770;
	kabeL[13][0][1] = 2430;
	kabeL[13][1][0] = 1200;
	kabeL[13][1][1] = 1230;
	kabeL[14][0][0] = 2010;
	kabeL[14][0][1] = 2040;
	kabeL[14][1][0] = 480;
	kabeL[14][1][1] = 720;
	kabeL[15][0][0] = 2160;
	kabeL[15][0][1] = 2190;
	kabeL[15][1][0] = 480;
	kabeL[15][1][1] = 720;
	kabeL[16][0][0] = 2160;
	kabeL[16][0][1] = 2430;
	kabeL[16][1][0] = 480;
	kabeL[16][1][1] = 510;
	kabeL[17][0][0] = 2160;
	kabeL[17][0][1] = 2430;
	kabeL[17][1][0] = 690;
	kabeL[17][1][1] = 720;
	kabeL[18][0][0] = 2400;
	kabeL[18][0][1] = 2430;
	kabeL[18][1][0] = -30;
	kabeL[18][1][1] = 510;
	kabeL[19][0][0] = 2400;
	kabeL[19][0][1] = 2430;
	kabeL[19][1][0] = 690;
	kabeL[19][1][1] = 1230;//左、右、上、下の順番。
	*/
	/*
	//ここからステージ3の壁の設定
	
	kabeL[0][0][0] = -30;
	kabeL[0][0][1] = 0;
	kabeL[0][1][0] = -110;
	kabeL[0][1][1] = 590;
	kabeL[1][0][0] = -30;
	kabeL[1][0][1] = 670;
	kabeL[1][1][0] = -110;
	kabeL[1][1][1] = -80;
	kabeL[2][0][0] = -30;
	kabeL[2][0][1] = 670;
	kabeL[2][1][0] = 560;
	kabeL[2][1][1] = 590;
	kabeL[3][0][0] = 640;
	kabeL[3][0][1] = 670;
	kabeL[3][1][0] = -30;
	kabeL[3][1][1] = 670;
	//ここからダメージ壁の設定
	kabeD[0][0][0] = 640;
	kabeD[0][0][1] = 680;
	kabeD[0][1][0] = -80;
	kabeD[0][1][1] = 0;
	kabeD[1][0][0] = 720;
	kabeD[1][0][1] = 760;
	kabeD[1][1][0] = 80;
	kabeD[1][1][1] = 160;
	kabeD[2][0][0] = 800;
	kabeD[2][0][1] = 840;
	kabeD[2][1][0] = 240;
	kabeD[2][1][1] = 320;
	kabeD[3][0][0] = 880;
	kabeD[3][0][1] = 920;
	kabeD[3][1][0] = 400;
	kabeD[3][1][1] = 480;
	kabeD[4][0][0] = 0;
	kabeD[4][0][1] = 80;
	kabeD[4][1][0] = -160-600;
	kabeD[4][1][1] = -80-600;
	kabeD[5][0][0] = 160;
	kabeD[5][0][1] = 240;
	kabeD[5][1][0] = -320-600;
	kabeD[5][1][1] = -240-600;
	kabeD[6][0][0] = 320;
	kabeD[6][0][1] = 400;
	kabeD[6][1][0] = -460-600;
	kabeD[6][1][1] = -380-600;
	kabeD[7][0][0] = 480;
	kabeD[7][0][1] = 560;
	kabeD[7][1][0] = -620-600;
	kabeD[7][1][1] = -540-600;
	kabeD[8][0][0] = 0-1200;
	kabeD[8][0][1] = -80-1200;
	kabeD[8][1][0] = 480;
	kabeD[8][1][1] = 560;
	kabeD[9][0][0] = -160-1200;
	kabeD[9][0][1] = -240-1200;
	kabeD[9][1][0] = 320;
	kabeD[9][1][1] = 400;
	kabeD[10][0][0] = -320-1200;
	kabeD[10][0][1] = -400-1200;
	kabeD[10][1][0] = 160;
	kabeD[10][1][1] = 240;
	kabeD[11][0][0] = -480-1200;
	kabeD[11][0][1] = -560-1200;
	kabeD[11][1][0] = 0;
	kabeD[11][1][1] = 80;
	kabeD[12][0][0] = 560;
	kabeD[12][0][1] = 640;
	kabeD[12][1][0] = 560+1800;
	kabeD[12][1][1] = 640+1800;
	kabeD[13][0][0] = 400;
	kabeD[13][0][1] = 480;
	kabeD[13][1][0] = 720+1800;
	kabeD[13][1][1] = 800+1800;
	kabeD[14][0][0] = 240;
	kabeD[14][0][1] = 320;
	kabeD[14][1][0] = 880+1800;
	kabeD[14][1][1] = 960+1800;
	kabeD[15][0][0] = 80;
	kabeD[15][0][1] = 160;
	kabeD[15][1][0] = 1040+1800;
	kabeD[15][1][1] = 1120+1800;
	//アイテムの個数の宣言
	k = 4;
	kaihukuaitemunokazu = 0;
	okaneaitemunokazu = 0;
	zakotekinokazu = 0;
	ututekinokazu = 4;
	utimakurutekinokazu = 0;
	
	


	//2700カウント後に4方向からダメージ壁を移動させるための設定
	if (genzainozikan == 2700) {
		kabeD[0][0][0] = 640;
		kabeD[0][0][1] = 680;
		kabeD[0][1][0] = -80;
		kabeD[0][1][1] = 0;
		kabeD[1][0][0] = 720;
		kabeD[1][0][1] = 760;
		kabeD[1][1][0] = 80;
		kabeD[1][1][1] = 160;
		kabeD[2][0][0] = 800;
		kabeD[2][0][1] = 840;
		kabeD[2][1][0] = 240;
		kabeD[2][1][1] = 320;
		kabeD[3][0][0] = 880;
		kabeD[3][0][1] = 920;
		kabeD[3][1][0] = 400;
		kabeD[3][1][1] = 480;
		kabeD[4][0][0] = 0;
		kabeD[4][0][1] = 80;
		kabeD[4][1][0] = -160;
		kabeD[4][1][1] = -80;
		kabeD[5][0][0] = 160;
		kabeD[5][0][1] = 240;
		kabeD[5][1][0] = -320;
		kabeD[5][1][1] = -240;
		kabeD[6][0][0] = 320;
		kabeD[6][0][1] = 400;
		kabeD[6][1][0] = -460;
		kabeD[6][1][1] = -380;
		kabeD[7][0][0] = 480;
		kabeD[7][0][1] = 560;
		kabeD[7][1][0] = -620;
		kabeD[7][1][1] = -540;
		kabeD[8][0][0] = 0;
		kabeD[8][0][1] = -80;
		kabeD[8][1][0] = 480;
		kabeD[8][1][1] = 560;
		kabeD[9][0][0] = -160;
		kabeD[9][0][1] = -240;
		kabeD[9][1][0] = 320;
		kabeD[9][1][1] = 400;
		kabeD[10][0][0] = -320;
		kabeD[10][0][1] = -400;
		kabeD[10][1][0] = 160;
		kabeD[10][1][1] = 240;
		kabeD[11][0][0] = -480;
		kabeD[11][0][1] = -560;
		kabeD[11][1][0] = 0;
		kabeD[11][1][1] = 80;
		kabeD[12][0][0] = 560;
		kabeD[12][0][1] = 640;
		kabeD[12][1][0] = 560;
		kabeD[12][1][1] = 640;
		kabeD[13][0][0] = 400;
		kabeD[13][0][1] = 480;
		kabeD[13][1][0] = 720;
		kabeD[13][1][1] = 800;
		kabeD[14][0][0] = 240;
		kabeD[14][0][1] = 320;
		kabeD[14][1][0] = 880;
		kabeD[14][1][1] = 960;
		kabeD[15][0][0] = 80;
		kabeD[15][0][1] = 160;
		kabeD[15][1][0] = 1040;
		kabeD[15][1][1] = 1120;
	}
	

	//ダメージ壁の移動の設定
	for (kurikaesi = 0; kurikaesi < 4; kurikaesi++) { kabeD[kurikaesi][0][0]--; kabeD[kurikaesi][0][1]--;}
	for (kurikaesi = 4; kurikaesi < 8; kurikaesi++) { kabeD[kurikaesi][1][0]++; kabeD[kurikaesi][1][1]++; }
	for (kurikaesi = 8; kurikaesi < 12; kurikaesi++) { kabeD[kurikaesi][0][0]++; kabeD[kurikaesi][0][1]++; }
	for (kurikaesi = 12; kurikaesi < 16; kurikaesi++) { kabeD[kurikaesi][1][0]--; kabeD[kurikaesi][1][1]--; }

	*/

	
	//ここからダメージ壁
	kabeD[0][0][0] = 50;
	kabeD[0][0][1] = 200;
	kabeD[0][1][0] = 390;
    kabeD[0][1][1] = 450;
	kabeD[1][0][0] = 400;
	kabeD[1][0][1] = 430;
	kabeD[1][1][0] = 200;
	kabeD[1][1][1] = 330;
	kabeD[2][0][0] = 30;
	kabeD[2][0][1] = 430;
	kabeD[2][1][0] = 300;
	kabeD[2][1][1] = 330;
	kabeD[3][0][0] = 0;
	kabeD[3][0][1] = 30;
	kabeD[3][1][0] = -470;
	kabeD[3][1][1] = -440;
	kabeD[4][0][0] = 30;
	kabeD[4][0][1] = 60;
	kabeD[4][1][0] = -440;
	kabeD[4][1][1] = -410;
	kabeD[5][0][0] = 60;
	kabeD[5][0][1] = 90;
	kabeD[5][1][0] = -410;
	kabeD[5][1][1] = -380;
	kabeD[6][0][0] = 90;
	kabeD[6][0][1] = 120;
	kabeD[6][1][0] = -380;
	kabeD[6][1][1] = -350;
	kabeD[7][0][0] = 120;
	kabeD[7][0][1] = 150;
	kabeD[7][1][0] = -350;
	kabeD[7][1][1] = -320;
	kabeD[8][0][0] = 150;
	kabeD[8][0][1] = 180;
	kabeD[8][1][0] = -320;
	kabeD[8][1][1] = -290;
	kabeD[9][0][0] = 180;
	kabeD[9][0][1] = 210;
	kabeD[9][1][0] = -290;
	kabeD[9][1][1] = -260;

	//ここから黒い壁。
	kuroikabe[0][0][0] = 300;
	kuroikabe[0][0][1] = 330;
	kuroikabe[0][1][0] = 100;
	kuroikabe[0][1][1] =130;

	//ここから集める壁。
	tannikabe[0][0][0] = 100;
	tannikabe[0][0][1] = 130;
	tannikabe[0][1][0] = 100;
	tannikabe[0][1][1] = 130;
	tannikabe[1][0][0] = 500;
	tannikabe[1][0][1] = 530;
	tannikabe[1][1][0] = -400;
	tannikabe[1][1][1] = -370;
	tannikabe[2][0][0] = 220;
	tannikabe[2][0][1] = 250;
	tannikabe[2][1][0] = -330;
	tannikabe[2][1][1] = -300;
	tannikabe[3][0][0] = 220;
	tannikabe[3][0][1] = 250;
	tannikabe[3][1][0] = -120;
	tannikabe[3][1][1] = -90;
	tannikabe[4][0][0] = 300;
	tannikabe[4][0][1] = 330;
	tannikabe[4][1][0] = -250;
	tannikabe[4][1][1] = -220;
	tannikabe[5][0][0] = 90;
	tannikabe[5][0][1] = 120;
	tannikabe[5][1][0] = -250;
	tannikabe[5][1][1] = -220;
	
	//セーブデータをロードする設定
	SaveData_t Data;
	FILE *fp;
	errno_t error;
	if (error = fopen_s(&fp, "セーブデータ.dat", "rb") != 0) {	//エラーの確認
		SaveData_t Data = { 100,10,4,0,0,1,1 };
		//FILE *fp;
		//errno_t error;
		if (error = fopen_s(&fp, "セーブデータ.dat", "wb") != 0) {	//エラーの確認
			return 0;	//エラー処理
		}
		fwrite(&Data, sizeof(Data), 1, fp);
		fclose(fp);
		
		tairyokusaidaiti = 100;//体力の最大値。最大は一応638かな。画面的に。
		kougekiryoku = 10;//自機の攻撃力。
		tamasokudo = 4;//弾の速度。レベルアップ有り。20かな。最大値は。
		okane = 0;//現在のお金の金額。
		okanenosaidaiti = 0;//お金の最大値。
		sokudo = 1;
		sutezinosaidaiti = 1;

	}
	else {
		fread(&Data, sizeof(Data), 1, fp);
		tairyokusaidaiti = Data.stairyokusaidaiti;//体力の最大値。最大は一応638かな。画面的に。
		kougekiryoku = Data.skougekiryoku;//自機の攻撃力。
		tamasokudo = Data.stamasokudo;//弾の速度。レベルアップ有り。20かな。最大値は。
		okane = Data.sokane;//現在のお金の金額。
		okanenosaidaiti = Data.sokanenosaidaiti;//お金の最大値。
		sokudo = Data.ssokudo;//移動速度最大は10かも。//tairyokusaidaiti,tairyoku,tairyokuzenkai,kougekiryoku,tamasokudo,okane,okanenosaidaiti,sokudo
		sutezinosaidaiti = Data.ssutezinosaidaiti;
		fclose(fp);
	}
	

	//メニュー画面の設定
	while(1){
		if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
		StopSoundMem(koukaongemuoba);//ゲームオーバーの音楽を止める。
		StopSoundMem(ongakusentou);//戦闘画面の音楽を止める。
		PlaySoundMem(ongakumenyu, DX_PLAYTYPE_LOOP);//メニュー画面の音楽再生。
		tairyoku = tairyokusaidaiti;
		tairyokuzenkai = tairyokusaidaiti;
	while (1)
	{
		if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1|| CheckHitKey(KEY_INPUT_Z) == 1||genzainosutezi!=0)
			break;
		if (CheckHitKey(KEY_INPUT_S) == 1) { okanenosaidaiti += 1000; }
		//DrawFormatString(100, 0, GetColor(255, 255, 255), "お金;%d", okane);
		//マウスの連続購入のプログラムとマウスの選択の状態(これから設定する予定)
		/*if (mausuhidariutu == 0) {
		if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 100) { mausuhidariutu = 30; tametamazikan2 = 0; }//30~50を使う。
		else if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 50) { mausuhidariutu = 10; tametamazikan1 = 0; }//10~20を使う。
		else if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 1)
		{
		mausuhidariutu = 0; mausuhidari = 0; mausuhidarizenkai = 0;
		}
		mausuhidarizenkai = mausuhidari;*/
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
			
		{
		mausuhidari++;
		// 押されている
		}
		//}
		if (mausuhidari == mausuhidarizenkai) { mausuhidari = 0; mausuhidarizenkai = 0; }
		mausuhidarizenkai = mausuhidari;
		
		
		if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)

		{
			mausumigi++;
			// 押されている
		}
		//}
		if (mausumigi == mausumigizenkai) { mausumigi = 0; mausumigizenkai = 0; }
		mausumigizenkai = mausumigi;
		GetMousePoint(&mausux, &mausuy);//マウスの座標を取得する。
		ClearDrawScreen();
		DrawGraph(0, 0, tyekkuhaikei, true);
		
										
										
										
										
										
										//画像描写ゾーン
		
		if (sutezinosaidaiti >= 1) {
			if (mausux > 50 && mausux < 110 && mausuy>30 && mausuy < 90) {
				DrawBox(45, 25, 115, 95, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 1; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);//選択したときの効果音の再生。
				}
				
			}  // 四角形を描画 
			DrawGraph(50, 30, sutezi1nogazou, true);
		}
		
		if (sutezinosaidaiti >= 2) {
			if (mausux > 140 && mausux < 200 && mausuy>30 && mausuy < 90) {
				DrawBox(135, 25, 205, 95, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 2; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(140, 30, sutezi2nogazou, true);
		}
		if (sutezinosaidaiti >= 3) {
			if (mausux >230  && mausux < 290 && mausuy>30 && mausuy < 90) {
				DrawBox(225, 25, 295, 95, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 3; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(230, 30, sutezi3nogazou, true);
		}
		if (sutezinosaidaiti >= 4) {
			if (mausux > 320 && mausux < 380 && mausuy>30 && mausuy < 90) {
				DrawBox(315, 25, 385, 95, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 4; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(320, 30, sutezi4nogazou, true);
		}
		if (sutezinosaidaiti >= 5) {
			if (mausux > 410 && mausux < 470 && mausuy>30 && mausuy < 90) {
				DrawBox(405, 25, 475, 95, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 5; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(410, 30, sutezi5nogazou, true);
		}
		if (sutezinosaidaiti >= 6) {
			if (mausux > 50 && mausux < 110 && mausuy>120 && mausuy < 180) {
				DrawBox(45, 115, 115, 185, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 6; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(50, 120, sutezi6nogazou, true);
		}
		if (sutezinosaidaiti >= 7) {
			if (mausux > 140 && mausux < 200 && mausuy>120 && mausuy < 180) {
				DrawBox(135, 115, 205, 185, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 7; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(140, 120, sutezi7nogazou, true);
		}
		if (sutezinosaidaiti >= 8) {
			if (mausux > 230 && mausux < 290 && mausuy>120 && mausuy < 180) {
				DrawBox(225, 115, 295, 185, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 8; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(230, 120, sutezi8nogazou, true);
		}
		if (sutezinosaidaiti >= 9) {
			if (mausux > 320 && mausux < 380 && mausuy>120 && mausuy < 180) {
				DrawBox(315, 115, 385, 185, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 9; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(320, 120, sutezi9nogazou, true);
		}
		if (sutezinosaidaiti >= 10) {
			if (mausux > 410 && mausux < 470 && mausuy>120 && mausuy < 180) {
				DrawBox(405, 115, 475, 185, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 10;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(410, 120, sutezi10nogazou, true);
		}
		if (sutezinosaidaiti >= 11) {
			if (mausux > 50 && mausux < 110 && mausuy>210 && mausuy < 270) {
				DrawBox(45, 205, 115, 275, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 11; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(50, 210, sutezi11nogazou, true);
		}
		if (sutezinosaidaiti >= 12) {
			if (mausux > 140 && mausux < 200 && mausuy>210 && mausuy < 270) {
				DrawBox(135, 205, 205, 275, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 12; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(140, 210, sutezi12nogazou, true);
		}
		if (sutezinosaidaiti >= 13) {
			if (mausux > 230 && mausux < 290 && mausuy>210 && mausuy < 270) {
				DrawBox(225, 205, 295, 275, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 13; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(230, 210, sutezi13nogazou, true);
		}
		if (sutezinosaidaiti >= 14) {
			if (mausux > 320 && mausux < 380 && mausuy>210 && mausuy < 270) {
				DrawBox(315, 205, 385, 275, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 14; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(320, 210, sutezi14nogazou, true);
		}
		if (sutezinosaidaiti >= 15) {
			if (mausux > 410 && mausux < 470 && mausuy>210 && mausuy < 270) {
				DrawBox(405, 205, 475, 275, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 15; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(410, 210, sutezi15nogazou, true);
		}
		if (sutezinosaidaiti >= 16) {
			if (mausux > 50 && mausux < 110 && mausuy>300 && mausuy < 360) {
				DrawBox(45, 295, 115, 365, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 16; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(50, 300, sutezi16nogazou, true);
		}
		if (sutezinosaidaiti >= 17) {
			if (mausux > 140 && mausux < 200 && mausuy>300 && mausuy < 360) {
				DrawBox(135, 295, 205, 365, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 17; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(140, 300, sutezi17nogazou, true);
		}
		if (sutezinosaidaiti >= 18) {
			if (mausux > 230 && mausux < 290 && mausuy>300 && mausuy < 360) {
				DrawBox(225, 295, 295, 365, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 18; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(230, 300, sutezi18nogazou, true);
		}
		if (sutezinosaidaiti >= 19) {
			if (mausux > 320 && mausux < 380 && mausuy>300 && mausuy < 360) {
				DrawBox(315, 295, 385, 365, GetColor(0, 0, 255), TRUE); sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 19; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(320, 300, sutezi19nogazou, true);
		}
		if (sutezinosaidaiti >= 20) {
			if (mausux > 410 && mausux < 470 && mausuy>300 && mausuy < 360) {
				DrawBox(405, 295, 475, 365, GetColor(0, 0, 255), TRUE);
				sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1) { genzainosutezi = 20; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 
			DrawGraph(410, 300, sutezi20nogazou, true);
		}
		//ステータスのやつ。
		
			
			
		
			if (mausux > 50 && mausux < 110 && mausuy>390 && mausuy < 450) {
				if (tairyokusaidaiti <= 630) {
				DrawBox(45, 385, 115, 455, GetColor(0, 0, 255), TRUE);// 四角形を描画 
				sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				}
				if (mausuhidari == 1 && okane >= 100 && tairyokusaidaiti == 100) { tairyoku = 120; tairyokusaidaiti = 120; okane -= 100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 200 && tairyokusaidaiti == 120) { tairyoku = 140; tairyokusaidaiti = 140; okane -= 200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 300 && tairyokusaidaiti == 140) { tairyoku = 160; tairyokusaidaiti = 160; okane -= 300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 400 && tairyokusaidaiti == 160) { tairyoku = 180; tairyokusaidaiti = 180; okane -= 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 500 && tairyokusaidaiti == 180) { tairyoku = 200; tairyokusaidaiti = 200; okane -= 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 600 && tairyokusaidaiti == 200) { tairyoku = 220; tairyokusaidaiti = 220; okane -= 600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 700 && tairyokusaidaiti == 220) { tairyoku = 240; tairyokusaidaiti = 240; okane -= 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 800 && tairyokusaidaiti == 240) { tairyoku = 260; tairyokusaidaiti = 260; okane -= 800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 900 && tairyokusaidaiti == 260) { tairyoku = 280; tairyokusaidaiti = 280; okane -= 900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1000 && tairyokusaidaiti == 280) { tairyoku = 300; tairyokusaidaiti = 300; okane -= 1000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1100 && tairyokusaidaiti == 300) { tairyoku = 320; tairyokusaidaiti = 320; okane -= 1100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1200 && tairyokusaidaiti == 320) { tairyoku = 340; tairyokusaidaiti = 340; okane -= 1200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1300 && tairyokusaidaiti == 340) { tairyoku = 360; tairyokusaidaiti = 360; okane -= 1300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1400 && tairyokusaidaiti == 360) { tairyoku = 380; tairyokusaidaiti = 380; okane -= 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1500 && tairyokusaidaiti == 380) { tairyoku = 400; tairyokusaidaiti = 400; okane -= 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1600 && tairyokusaidaiti == 400) { tairyoku = 420; tairyokusaidaiti = 420; okane -= 1600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1700 && tairyokusaidaiti == 420) { tairyoku = 440; tairyokusaidaiti = 440; okane -= 1700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1800 && tairyokusaidaiti == 440) { tairyoku = 460; tairyokusaidaiti = 460; okane -= 1800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1900 && tairyokusaidaiti == 460) { tairyoku = 480; tairyokusaidaiti = 480; okane -= 1900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2000 && tairyokusaidaiti == 480) { tairyoku = 500; tairyokusaidaiti = 500; okane -= 2000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2100 && tairyokusaidaiti == 500) { tairyoku = 520; tairyokusaidaiti = 520; okane -= 2100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2200 && tairyokusaidaiti == 520) { tairyoku = 540; tairyokusaidaiti = 540; okane -= 2200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2300 && tairyokusaidaiti == 540) { tairyoku = 560; tairyokusaidaiti = 560; okane -= 2300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2400 && tairyokusaidaiti == 560) { tairyoku = 580; tairyokusaidaiti = 580; okane -= 2400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2500 && tairyokusaidaiti == 580) { tairyoku = 600; tairyokusaidaiti = 600; okane -= 2500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2600 && tairyokusaidaiti == 600) { tairyoku = 620; tairyokusaidaiti = 620; okane -= 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2700 && tairyokusaidaiti == 620) { tairyoku = 638; tairyokusaidaiti = 638; okane -= 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  
			
			if (tairyokusaidaiti == 100) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;100"); }
			else if (tairyokusaidaiti == 120) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;200"); }
			else if (tairyokusaidaiti == 140) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;300"); }
			else if (tairyokusaidaiti == 160) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;400"); }
			else if (tairyokusaidaiti == 180) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;500"); }
			else if (tairyokusaidaiti == 200) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;600"); }
			else if (tairyokusaidaiti == 220) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;700"); }
			else if (tairyokusaidaiti == 240) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;800"); }
			else if (tairyokusaidaiti == 260) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;900"); }
			else if (tairyokusaidaiti == 280) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1000"); }
			else if (tairyokusaidaiti == 300) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1100"); }
			else if (tairyokusaidaiti == 320) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1200"); }
			else if (tairyokusaidaiti == 340) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1300"); }
			else if (tairyokusaidaiti == 360) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1400"); }
			else if (tairyokusaidaiti == 380) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1500"); }
			else if (tairyokusaidaiti == 400) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1600"); }
			else if (tairyokusaidaiti == 420) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1700"); }
			else if (tairyokusaidaiti == 440) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1800"); }
			else if (tairyokusaidaiti == 460) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;1900"); }
			else if (tairyokusaidaiti == 480) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2000"); }
			else if (tairyokusaidaiti == 500) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2100"); }
			else if (tairyokusaidaiti == 520) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2200"); }
			else if (tairyokusaidaiti == 540) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2300"); }
			else if (tairyokusaidaiti == 560) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2400"); }
			else if (tairyokusaidaiti == 580) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2500"); }
			else if (tairyokusaidaiti == 600) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2600"); }
			else if (tairyokusaidaiti == 620) { DrawFormatString(50, 455, GetColor(0, 0, 0), "$;2700"); }
			else if (tairyokusaidaiti == 638) { DrawFormatString(50, 455, GetColor(0, 0, 0), "MAX"); }
			DrawFormatString(47, 370, GetColor(0, 0, 0), "LIFE;%d", tairyokusaidaiti);
			
		
		
			if (mausux > 140 && mausux < 200 && mausuy>390 && mausuy < 450) {
				if (kougekiryoku <= 36) {
					DrawBox(135, 385, 205, 455, GetColor(0, 0, 255), TRUE);
					sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				}
				if (mausuhidari == 1 && okane >= 100 && kougekiryoku == 10) { kougekiryoku = 11;  okane -= 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 200 && kougekiryoku == 11) { kougekiryoku = 12; okane -= 200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 300 && kougekiryoku == 12) { kougekiryoku = 13; okane -= 300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 400 && kougekiryoku == 13) { kougekiryoku = 14;  okane -= 400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 500 && kougekiryoku == 14) { kougekiryoku = 15; okane -= 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 600 && kougekiryoku == 15) { kougekiryoku = 16;  okane -= 600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 700 && kougekiryoku == 16) { kougekiryoku = 17;  okane -= 700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 800 && kougekiryoku == 17) { kougekiryoku = 18;  okane -= 800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 900 && kougekiryoku == 18) { kougekiryoku = 19;  okane -= 900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1000 && kougekiryoku == 19) { kougekiryoku = 20;  okane -= 1000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1100 && kougekiryoku == 20) { kougekiryoku = 21;  okane -= 1100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1200 && kougekiryoku == 21) { kougekiryoku = 22;  okane -= 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1300 && kougekiryoku == 22) { kougekiryoku = 23;  okane -= 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1400 && kougekiryoku == 23) { kougekiryoku = 24;  okane -= 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1500 && kougekiryoku == 24) { kougekiryoku = 25;  okane -= 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1600 && kougekiryoku == 25) { kougekiryoku = 26;  okane -= 1600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1700 && kougekiryoku == 26) { kougekiryoku = 27;  okane -= 1700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1800 && kougekiryoku == 27) { kougekiryoku = 28;  okane -= 1800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1900 && kougekiryoku == 28) { kougekiryoku = 29;  okane -= 1900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2000 && kougekiryoku == 29) { kougekiryoku = 30; okane -= 2000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2100 && kougekiryoku == 30) { kougekiryoku = 31;  okane -= 2100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2200 && kougekiryoku == 31) { kougekiryoku = 32;  okane -= 2200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2300 && kougekiryoku == 32) { kougekiryoku = 33;  okane -= 2300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2400 && kougekiryoku == 33) { kougekiryoku = 34;  okane -= 2400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2500 && kougekiryoku == 34) { kougekiryoku = 35; okane -= 2500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2600 && kougekiryoku == 35) { kougekiryoku = 36;  okane -= 2600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2700 && kougekiryoku == 36) { kougekiryoku = 37; okane -= 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}

			
		}  
		if (kougekiryoku == 10) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;100"); }
		else if (kougekiryoku == 11) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;200"); }
		else if (kougekiryoku == 12) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;300"); }
		else if (kougekiryoku == 13) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;400"); }
		else if (kougekiryoku == 14) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;500"); }
		else if (kougekiryoku == 15) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;600"); }
		else if (kougekiryoku == 16) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;700"); }
		else if (kougekiryoku == 17) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;800"); }
		else if (kougekiryoku == 18) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;900"); }
		else if (kougekiryoku == 19) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1000"); }
		else if (kougekiryoku == 20) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1100"); }
		else if (kougekiryoku == 21) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1200"); }
		else if (kougekiryoku == 22) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1300"); }
		else if (kougekiryoku == 23) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1400"); }
		else if (kougekiryoku == 24) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1500"); }
		else if (kougekiryoku == 25) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1600"); }
		else if (kougekiryoku == 26) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1700"); }
		else if (kougekiryoku == 27) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1800"); }
		else if (kougekiryoku == 28) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;1900"); }
		else if (kougekiryoku == 29) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2000"); }
		else if (kougekiryoku == 30) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2100"); }
		else if (kougekiryoku == 31) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2200"); }
		else if (kougekiryoku == 32) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2300"); }
		else if (kougekiryoku == 33) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2400"); }
		else if (kougekiryoku == 34) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2500"); }
		else if (kougekiryoku == 35) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2600"); }
		else if (kougekiryoku == 36) { DrawFormatString(135, 455, GetColor(0, 0, 0), "$;2700"); }
		else if (kougekiryoku == 37) { DrawFormatString(135, 455, GetColor(0, 0, 0), "MAX"); }
		
		
		DrawFormatString(140, 370, GetColor(0, 0, 0), "POWER;%d", kougekiryoku);
				
		
		
			if (mausux > 230 && mausux < 290 && mausuy>390 && mausuy < 450) {
				if (sokudo < 3.7) {
					DrawBox(225, 385, 295, 455, GetColor(0, 0, 255), TRUE);
					sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				}
				if (mausuhidari == 1 && okane >= 100 && sokudo == 1) { sokudo = 1.1;  okane -= 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 200 && sokudo == 1.1) { sokudo = 1.2; okane -= 200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 300 && sokudo == 1.2) { sokudo = 1.3; okane -= 300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 400 && sokudo == 1.3) { sokudo = 1.4;  okane -= 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 500 && sokudo == 1.4) { sokudo = 1.5;  okane -= 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 600 && sokudo == 1.5) { sokudo = 1.6;  okane -= 600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 700 && sokudo == 1.6) { sokudo = 1.7;  okane -= 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 800 && sokudo == 1.7) { sokudo = 1.8;  okane -= 800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 900 && sokudo == 1.8) { sokudo = 1.9;  okane -= 900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1000 && sokudo == 1.9) { sokudo = 2.0;  okane -= 1000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1100 && sokudo == 2.0) { sokudo = 2.1;  okane -= 1100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1200 && sokudo == 2.1) { sokudo = 2.2;  okane -= 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1300 && sokudo == 2.2) { sokudo = 2.3;  okane -= 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1400 && sokudo == 2.3) { sokudo = 2.4;  okane -= 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1500 && sokudo == 2.4) { sokudo = 2.5;  okane -= 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1600 && sokudo == 2.5) { sokudo = 2.6;  okane -= 1600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1700 && sokudo == 2.6) { sokudo = 2.7;  okane -= 1700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1800 && sokudo == 2.7) { sokudo = 2.8;  okane -= 1800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1900 && sokudo == 2.8) { sokudo = 2.9;  okane -= 1900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2000 && sokudo == 2.9) { sokudo = 3.0; okane -= 2000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2100 && sokudo == 3.0) { sokudo = 3.1;  okane -= 2100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2200 && sokudo == 3.1) { sokudo = 3.2;  okane -= 2200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2300 && sokudo == 3.2) { sokudo = 3.3;  okane -= 2300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2400 && sokudo == 3.3) { sokudo = 3.4;  okane -= 2400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2500 && sokudo == 3.4) { sokudo = 3.5; okane -= 2500;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2600 && sokudo == 3.5) { sokudo = 3.6;  okane -= 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2700 && sokudo == 3.6) { sokudo = 3.7; okane -= 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  // 四角形を描画 			
		
		if (sokudo == 1) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;100"); }
		else if (sokudo == 1.1) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;200"); }
		else if (sokudo == 1.2) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;300"); }
		else if (sokudo == 1.3) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;400"); }
		else if (sokudo == 1.4) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;500"); }
		else if (sokudo == 1.5) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;600"); }
		else if (sokudo == 1.6) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;700"); }
		else if (sokudo == 1.7) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;800"); }
		else if (sokudo == 1.8) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;900"); }
		else if (sokudo == 1.9) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1000"); }
		else if (sokudo == 2.0) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1100"); }
		else if (sokudo == 2.1) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1200"); }
		else if (sokudo == 2.2) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1300"); }
		else if (sokudo == 2.3) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1400"); }
		else if (sokudo == 2.4) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1500"); }
		else if (sokudo == 2.5) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1600"); }
		else if (sokudo == 2.6) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1700"); }
		else if (sokudo == 2.7) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1800"); }
		else if (sokudo == 2.8) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;1900"); }
		else if (sokudo == 2.9) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2000"); }
		else if (sokudo == 3.0) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2100"); }
		else if (sokudo == 3.1) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2200"); }
		else if (sokudo == 3.2) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2300"); }
		else if (sokudo == 3.3) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2400"); }
		else if (sokudo == 3.4) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2500"); }
		else if (sokudo == 3.5) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2600"); }
		else if (sokudo == 3.6) { DrawFormatString(230, 455, GetColor(0, 0, 0), "$;2700"); }
		else if (sokudo == 3.7) { DrawFormatString(230, 455, GetColor(0, 0, 0), "MAX"); }
		DrawFormatString(230, 370, GetColor(0, 0, 0), "SPEED;%2.1f", sokudo+0.000000001);//2進数に直したりする処理の関係でちょっと足してる。
		
			if (mausux > 320 && mausux < 380 && mausuy>390 && mausuy < 450) {
				if (tamasokudo < 30) {
					DrawBox(315, 385, 385, 455, GetColor(0, 0, 255), TRUE);
					sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				}
				if (mausuhidari == 1 && okane >= 100 && tamasokudo == 4) { tamasokudo = 4.2;  okane -= 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 200 && tamasokudo == 4.2) { tamasokudo = 4.4; okane -= 200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 300 && tamasokudo == 4.4) { tamasokudo = 4.6; okane -= 300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 400 && tamasokudo == 4.6) { tamasokudo = 4.8;  okane -= 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 500 && tamasokudo == 4.8) { tamasokudo = 5.0; okane -= 500;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 600 && tamasokudo == 5.0) { tamasokudo = 5.2;  okane -= 600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 700 && tamasokudo == 5.2) { tamasokudo = 5.4;  okane -= 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 800 && tamasokudo == 5.4) { tamasokudo = 5.6;  okane -= 800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 900 && tamasokudo == 5.6) { tamasokudo = 5.8;  okane -= 900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1000 && tamasokudo == 5.8) { tamasokudo = 6.0;  okane -= 1000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1100 && tamasokudo == 6.0) { tamasokudo = 6.2;  okane -= 1100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1200 && tamasokudo == 6.2) { tamasokudo = 6.4;  okane -= 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1300 && tamasokudo == 6.4) { tamasokudo = 6.6;  okane -= 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1400 && tamasokudo == 6.6) { tamasokudo = 6.8;  okane -= 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1500 && tamasokudo == 6.8) { tamasokudo = 7.0;  okane -= 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1600 && tamasokudo == 7.0) { tamasokudo = 7.2;  okane -= 1600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1700 && tamasokudo == 7.2) { tamasokudo = 7.4;  okane -= 1700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1800 && tamasokudo == 7.4) { tamasokudo = 7.6;  okane -= 1800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 1900 && tamasokudo == 7.6) { tamasokudo = 7.8;  okane -= 1900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2000 && tamasokudo == 7.8) { tamasokudo = 8.0; okane -= 2000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2100 && tamasokudo == 8.0) { tamasokudo = 8.2;  okane -= 2100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2200 && tamasokudo == 8.2) { tamasokudo = 8.4;  okane -= 2200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2300 && tamasokudo == 8.4) { tamasokudo = 8.6;  okane -= 2300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2400 && tamasokudo == 8.6) { tamasokudo = 8.8;  okane -= 2400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2500 && tamasokudo == 8.8) { tamasokudo = 9.0; okane -= 2500;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2600 && tamasokudo == 9.0) { tamasokudo = 9.2;  okane -= 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausuhidari == 1 && okane >= 2700 && tamasokudo == 9.2) { tamasokudo = 9.4; okane -= 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}  
			if (tamasokudo == 4) { DrawFormatString(320, 455, GetColor(0,0,0), "$;100"); }
			else if (tamasokudo == 4.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;200"); }
			else if (tamasokudo == 4.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;300"); }
			else if (tamasokudo == 4.6) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;400"); }
			else if (tamasokudo == 4.8) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;500"); }
			else if (tamasokudo == 5.0) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;600"); }
			else if (tamasokudo == 5.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;700"); }
			else if (tamasokudo == 5.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;800"); }
			else if (tamasokudo == 5.6) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;900"); }
			else if (tamasokudo == 5.8) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1000"); }
			else if (tamasokudo == 6.0) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1100"); }
			else if (tamasokudo == 6.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1200"); }
			else if (tamasokudo == 6.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1300"); }
			else if (tamasokudo == 6.6) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1400"); }
			else if (tamasokudo == 6.8) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1500"); }
			else if (tamasokudo == 7.0) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1600"); }
			else if (tamasokudo == 7.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1700"); }
			else if (tamasokudo == 7.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1800"); }
			else if (tamasokudo == 7.6) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;1900"); }
			else if (tamasokudo == 7.8) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2000"); }
			else if (tamasokudo == 8.0) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2100"); }
			else if (tamasokudo == 8.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2200"); }
			else if (tamasokudo == 8.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2300"); }
			else if (tamasokudo == 8.6) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2400"); }
			else if (tamasokudo == 8.8) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2500"); }
			else if (tamasokudo == 9.0) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2600"); }
			else if (tamasokudo == 9.2) { DrawFormatString(320, 455, GetColor(0, 0, 0), "$;2700"); }
			else if (tamasokudo == 9.4) { DrawFormatString(320, 455, GetColor(0, 0, 0), "MAX"); }
			
			//右クリックで返品の設定
			if (mausux > 50 && mausux < 110 && mausuy>390 && mausuy < 450) {
				if (mausumigi == 1 &&  tairyokusaidaiti == 120) {
					tairyoku = 100; tairyokusaidaiti = 100; okane += 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 140) {
					tairyoku = 120; tairyokusaidaiti = 120; okane += 200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 160) {
					tairyoku = 140; tairyokusaidaiti = 140; okane += 300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 180) {
					tairyoku = 160; tairyokusaidaiti = 160; okane += 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 200) {
					tairyoku = 180; tairyokusaidaiti = 180; okane += 500;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 220) {
					tairyoku = 200; tairyokusaidaiti = 200; okane += 600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 240) {
					tairyoku = 220; tairyokusaidaiti = 220; okane += 700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 260) {
					tairyoku = 240; tairyokusaidaiti = 240; okane += 800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 280) {
					tairyoku = 260; tairyokusaidaiti = 260; okane += 900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 300) {
					tairyoku = 280; tairyokusaidaiti = 280; okane += 1000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 320) {
					tairyoku = 300; tairyokusaidaiti = 300; okane += 1100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 340) {
					tairyoku = 320; tairyokusaidaiti = 320; okane += 1200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 360) {
					tairyoku = 340; tairyokusaidaiti = 340; okane += 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 380) {
					tairyoku = 360; tairyokusaidaiti = 360; okane += 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 400) {
					tairyoku = 380; tairyokusaidaiti = 380; okane += 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 420) {
					tairyoku = 400; tairyokusaidaiti = 400; okane += 1600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 440) {
					tairyoku = 420; tairyokusaidaiti = 420; okane += 1700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 460) {
					tairyoku = 440; tairyokusaidaiti = 440; okane += 1800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 480) {
					tairyoku = 460; tairyokusaidaiti = 460; okane += 1900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 500) {
					tairyoku = 480; tairyokusaidaiti = 480; okane += 2000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 520) {
					tairyoku = 500; tairyokusaidaiti = 500; okane += 2100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 540) {
					tairyoku = 520; tairyokusaidaiti = 520; okane += 2200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 560) {
					tairyoku = 540; tairyokusaidaiti = 540; okane += 2300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 580) {
					tairyoku = 560; tairyokusaidaiti = 560; okane += 2400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 600) {
					tairyoku = 580; tairyokusaidaiti = 580; okane += 2500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 620) {
					tairyoku = 600; tairyokusaidaiti = 600; okane += 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tairyokusaidaiti == 638) {
					tairyoku = 620; tairyokusaidaiti = 620; okane += 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}
			if (mausux > 140 && mausux < 200 && mausuy>390 && mausuy < 450) {
				if (mausumigi == 1 && kougekiryoku == 11) {
					kougekiryoku = 10; okane += 100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 12) {
					kougekiryoku = 11; okane += 200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 13) {
					kougekiryoku = 12;  okane += 300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 14) {
					kougekiryoku = 13; okane += 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 15) {
					kougekiryoku = 14;  okane += 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 16) {
					kougekiryoku = 15;  okane += 600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 17) {
					kougekiryoku = 16;  okane += 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 18) {
					kougekiryoku = 17;  okane += 800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 19) {
					kougekiryoku = 18;  okane += 900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 20) {
					kougekiryoku = 19;  okane += 1000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 21) {
					kougekiryoku = 20;  okane += 1100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 22) {
					kougekiryoku = 21;  okane += 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 23) {
					kougekiryoku = 22;  okane += 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 24) {
					kougekiryoku = 23;  okane += 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 25) {
					kougekiryoku = 24;  okane += 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 26) {
					kougekiryoku = 25;  okane += 1600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 27) {
					kougekiryoku = 26;  okane += 1700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 28) {
					kougekiryoku = 27;  okane += 1800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 29) {
					kougekiryoku = 28; okane += 1900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 30) {
					kougekiryoku = 29;  okane += 2000;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 31) {
					kougekiryoku = 30;  okane += 2100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 32) {
					kougekiryoku = 31;  okane += 2200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 33) {
					kougekiryoku = 32;  okane += 2300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 34) {
					kougekiryoku = 33; okane += 2400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 35) {
					kougekiryoku = 34;  okane += 2500;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 36) {
					kougekiryoku = 35; okane += 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && kougekiryoku == 37) {
					kougekiryoku = 36; okane += 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}
			if (mausux > 230 && mausux < 290 && mausuy>390 && mausuy < 450) {
				if (mausumigi == 1 && sokudo == 1.1) {
					sokudo = 1; okane += 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.2) {
					sokudo = 1.1; okane += 200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.3) {
					sokudo = 1.2;  okane += 300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.4) {
					sokudo = 1.3;  okane += 400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.5) {
					sokudo = 1.4;  okane += 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.6) {
					sokudo = 1.5;  okane += 600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.7) {
					sokudo = 1.6;  okane += 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.8) {
					sokudo = 1.7;  okane += 800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 1.9) {
					sokudo = 1.8;  okane += 900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.0) {
					sokudo = 1.9;  okane += 1000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.1) {
					sokudo = 2.0;  okane += 1100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.2) {
					sokudo = 2.1;  okane += 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.3) {
					sokudo = 2.2;  okane += 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.4) {
					sokudo = 2.3;  okane += 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.5) {
					sokudo = 2.4;  okane += 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.6) {
					sokudo = 2.5;  okane += 1600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.7) {
					sokudo = 2.6;  okane += 1700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.8) {
					sokudo = 2.7;  okane += 1800;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 2.9) {
					sokudo = 2.8; okane += 1900;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.0) {
					sokudo = 2.9;  okane += 2000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.1) {
					sokudo = 3.0;  okane += 2100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.2) {
					sokudo = 3.1;  okane += 2200;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.3) {
					sokudo = 3.2;  okane += 2300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.4) {
					sokudo = 3.3; okane += 2400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.5) {
					sokudo = 3.4;  okane += 2500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.6) {
					sokudo = 3.5; okane += 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && sokudo == 3.7) {
					sokudo = 3.6; okane += 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}	
			if (mausux > 320 && mausux < 380 && mausuy>390 && mausuy < 450) {
				
				if (mausumigi == 1 && tamasokudo == 4.2) {
					tamasokudo = 4; okane += 100;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 4.4) {
					tamasokudo = 4.2; okane += 200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 4.6) {
					tamasokudo = 4.4;  okane += 300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 4.8) {
					tamasokudo = 4.6; okane += 400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 5.0) {
					tamasokudo = 4.8;  okane += 500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 5.2) {
					tamasokudo = 5.0;  okane += 600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 5.4) {
					tamasokudo = 5.2;  okane += 700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 5.6) {
					tamasokudo = 5.4;  okane += 800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 5.8) {
					tamasokudo = 5.6;  okane += 900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 6.0) {
					tamasokudo = 5.8;  okane += 1000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 6.2) {
					tamasokudo = 6.0;  okane += 1100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 6.4) {
					tamasokudo = 6.2;  okane += 1200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 6.6) {
					tamasokudo = 6.4;  okane += 1300; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 6.8) {
					tamasokudo = 6.6;  okane += 1400; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 7.0) {
					tamasokudo = 6.8;  okane += 1500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 7.2) {
					tamasokudo = 7.0;  okane += 1600;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 7.4) {
					tamasokudo = 7.2;  okane += 1700;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 7.6) {
					tamasokudo = 7.4;  okane += 1800; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 7.8) {
					tamasokudo = 7.6; okane += 1900; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 8.0) {
					tamasokudo = 7.8;  okane += 2000; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 8.2) {
					tamasokudo = 8.0;  okane += 2100; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 8.4) {
					tamasokudo = 8.2;  okane += 2200; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 8.6) {
					tamasokudo = 8.4;  okane += 2300;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 8.8) {
					tamasokudo = 8.6; okane += 2400;  PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 9.0) {
					tamasokudo = 8.8;  okane += 2500; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 9.2) {
					tamasokudo = 9.0; okane += 2600; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
				else if (mausumigi == 1 && tamasokudo == 9.4) {
					tamasokudo = 9.2; okane += 2700; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}
		DrawFormatString(320, 370, GetColor(0, 0, 0), "RANGE;%1.1f", tamasokudo+0.00000001);
		DrawFormatString(400, 370, GetColor(0, 0, 0), "$;%d/%d", okane,okanenosaidaiti);
		DrawFormatString(470, 400, GetColor(0, 0, 0), "←振り分けやり直しで\n　購入初期化");
		DrawFormatString(60, 300, GetColor(0, 0, 0), "           左クリックで購入\n           右クリックで売却\n  ↓        ↓        ↓        ↓");
		DrawFormatString(60, 200, GetColor(0, 0, 0), "↑      左クリックでステージ選択\n      全部で8ステージあります");
		DrawFormatString(500, 200, GetColor(0, 0, 0), "　　↑\n左クリックで\nセーブします");
		if (mausux > 410 && mausux < 470 && mausuy>390 && mausuy < 450) {
			if (okane!=okanenosaidaiti) {
				DrawBox(405, 385, 475, 455, GetColor(0, 0, 255), TRUE);
				sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
				if (mausuhidari == 1 && okane != okanenosaidaiti) { tairyoku = 100; tairyokusaidaiti = 100; kougekiryoku = 10; sokudo = 1; tamasokudo = 4;  okane = okanenosaidaiti; PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				}
			}
		}
		//セーブのところ
		if (mausux > 500 && mausux < 590 && mausuy>120 && mausuy < 180) {

			DrawBox(495, 115, 595, 185, GetColor(0, 0, 255), TRUE);
			sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
			if (mausuhidari == 1) {
				PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				SaveData_t Data = { tairyokusaidaiti,kougekiryoku,tamasokudo,okane,okanenosaidaiti,sokudo,sutezinosaidaiti };
				FILE *fp;
				errno_t error;
				if (error = fopen_s(&fp, "セーブデータ.dat", "wb") != 0) {	//エラーの確認
					return 0;	//エラー処理
				}
				fwrite(&Data, sizeof(Data), 1, fp);
				fclose(fp);
				//return 0;
			}
		}
		
		/*
		//遊び方のところ
		if (mausux > 500 && mausux < 590 && mausuy>210 && mausuy < 270) {

			DrawBox(495, 205, 595, 275, GetColor(0, 0, 255), TRUE);
			sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
			if (mausuhidari == 1) {
				PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				SaveData_t Data;
				FILE *fp;
				errno_t error;
				if (error = fopen_s(&fp, "セーブデータ.dat", "rb") != 0) {	//エラーの確認
					tairyokusaidaiti = 100;//体力の最大値。最大は一応638かな。画面的に。
					kougekiryoku = 10;//自機の攻撃力。
					tamasokudo = 4;//弾の速度。レベルアップ有り。20かな。最大値は。
					okane = 0;//現在のお金の金額。
					okanenosaidaiti = 0;//お金の最大値。
					sokudo = 1;
																		
																		
					//return 0;	//エラー処理
				}
				fread(&Data, sizeof(Data), 1, fp);
				tairyokusaidaiti = Data.stairyokusaidaiti;//体力の最大値。最大は一応638かな。画面的に。
				kougekiryoku = Data.skougekiryoku;//自機の攻撃力。
				tamasokudo = Data.stamasokudo;//弾の速度。レベルアップ有り。20かな。最大値は。
				okane = Data.sokane;//現在のお金の金額。
				okanenosaidaiti = Data.sokanenosaidaiti;//お金の最大値。
				sokudo = Data.ssokudo;//移動速度最大は10かも。//tairyokusaidaiti,tairyoku,tairyokuzenkai,kougekiryoku,tamasokudo,okane,okanenosaidaiti,sokudo
				sutezinosaidaiti = Data.ssutezinosaidaiti;
				fclose(fp);
				

			}
		}
		*/
		/*
		//設定のところ
		if (mausux > 500 && mausux < 590 && mausuy>300 && mausuy < 360) {

			DrawBox(495, 295, 595, 365, GetColor(0, 0, 255), TRUE);
			sentakujoutai += 1;//マウスを範囲内に合わせたときの効果音の設定
			if (mausuhidari == 1) {
				PlaySoundMem(koukaonkurikku, DX_PLAYTYPE_BACK);
				

			}
		}*/
		if (sentakujoutai == 1) { PlaySoundMem(koukaonsentaku, DX_PLAYTYPE_BACK); }
		
		if (sentakujoutai == sentakujoutaizenkai) { sentakujoutai = 0; sentakujoutaizenkai = 0; }
		sentakujoutaizenkai = sentakujoutai;

		DrawExtendGraph(50,390,110,450, lifenogazou, false);
		DrawExtendGraph(140, 390, 200, 450, powernogazou, false);
		DrawExtendGraph(230, 390, 290, 450, speednogazou, false);
		DrawExtendGraph(320, 390, 380, 450, rangenogazou, false);
		DrawExtendGraph(410, 390, 470, 450, huriwakeyarinaosinogazou, false);
		//DrawGraph(500, 30, pureizikannnogazou, true);
		DrawGraph(500, 120, sebunogazou, true);
		//DrawGraph(500, 210, asobikatanogazou, true);
		//DrawGraph(500, 300, setteinogazou, true);
	
		
		ScreenFlip();
		//画像描画ゾーン,画面の大きさは、640*480
	}
	//メニューと本編の間にステージの設定をする。
	
	
	if (genzainosutezi == 1) {
		k = 20;//壁の個数k個ある。
		n = 4;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 2;
		okaneaitemunokazu = 1;
		kaihukuaitemunokazu = 1;
		memonokazu = 6;
		tanninokazu = 1;
		tannihituyousuu = 1;
		zakotekinokazu = 0;
		ututekinokazu = 0;
		utimakurutekinokazu = 1;
		dekaitekinokazu = 0;
		damezikabenokougekiryoku = 10;
		//ここからステージ1の緑の壁の設定。
		kabeL[0][0][0] = -30;
		kabeL[0][0][1] = 0;
		kabeL[0][1][0] = -30;
		kabeL[0][1][1] = 480;
		kabeL[1][0][0] = -30;
		kabeL[1][0][1] = 1230;
		kabeL[1][1][0] = -30;
		kabeL[1][1][1] = 0;
		kabeL[2][0][0] = -30;
		kabeL[2][0][1] = 1230;
		kabeL[2][1][0] = 480;
		kabeL[2][1][1] = 510;
		kabeL[3][0][0] = 1200;
		kabeL[3][0][1] = 1230;
		kabeL[3][1][0] = -30;
		kabeL[3][1][1] = 180;
		kabeL[4][0][0] = 1200;
		kabeL[4][0][1] = 1230;
		kabeL[4][1][0] = 300;
		kabeL[4][1][1] = 510;
		kabeL[5][0][0] = 1200;
		kabeL[5][0][1] = 1800;
		kabeL[5][1][0] = 150;
		kabeL[5][1][1] = 180;
		kabeL[6][0][0] = 1200;
		kabeL[6][0][1] = 1800;
		kabeL[6][1][0] = 300;
		kabeL[6][1][1] = 330;
		kabeL[7][0][0] = 1770;
		kabeL[7][0][1] = 1800;
		kabeL[7][1][0] = -30;
		kabeL[7][1][1] = 180;
		kabeL[8][0][0] = 1770;
		kabeL[8][0][1] = 1800;
		kabeL[8][1][0] = 300;
		kabeL[8][1][1] = 510;
		kabeL[9][0][0] = 1770;
		kabeL[9][0][1] = 1800;
		kabeL[9][1][0] = 690;
		kabeL[9][1][1] = 1230;
		kabeL[10][0][0] = 1770;
		kabeL[10][0][1] = 2430;
		kabeL[10][1][0] = -30;
		kabeL[10][1][1] = 0;
		kabeL[11][0][0] = 1770;
		kabeL[11][0][1] = 2040;
		kabeL[11][1][0] = 480;
		kabeL[11][1][1] = 510;
		kabeL[12][0][0] = 1770;
		kabeL[12][0][1] = 2040;
		kabeL[12][1][0] = 690;
		kabeL[12][1][1] = 720;
		kabeL[13][0][0] = 1770;
		kabeL[13][0][1] = 2430;
		kabeL[13][1][0] = 1200;
		kabeL[13][1][1] = 1230;
		kabeL[14][0][0] = 2010;
		kabeL[14][0][1] = 2040;
		kabeL[14][1][0] = 480;
		kabeL[14][1][1] = 720;
		kabeL[15][0][0] = 2160;
		kabeL[15][0][1] = 2190;
		kabeL[15][1][0] = 480;
		kabeL[15][1][1] = 720;
		kabeL[16][0][0] = 2160;
		kabeL[16][0][1] = 2430;
		kabeL[16][1][0] = 480;
		kabeL[16][1][1] = 510;
		kabeL[17][0][0] = 2160;
		kabeL[17][0][1] = 2430;
		kabeL[17][1][0] = 690;
		kabeL[17][1][1] = 720;
		kabeL[18][0][0] = 2400;
		kabeL[18][0][1] = 2430;
		kabeL[18][1][0] = -30;
		kabeL[18][1][1] = 510;
		kabeL[19][0][0] = 2400;
		kabeL[19][0][1] = 2430;
		kabeL[19][1][0] = 690;
		kabeL[19][1][1] = 1230;//左、右、上、下の順番。

		memo[0][0] = 265; memo[0][1] = 180;
		memo[1][0] = 800; memo[1][1] = 240;
		memo[2][0] = 1300; memo[2][1] = 40;
		memo[3][0] = 2000; memo[3][1] = 240;
		memo[4][0] = 2040; memo[4][1] = 540;
		memo[5][0] = 1900; memo[5][1] = 900;

		kabeD[0][0][0] = 1770;
		kabeD[0][0][1] = 1800;
		kabeD[0][1][0] = 180;
		kabeD[0][1][1] =210;
		kabeD[1][0][0] = 1770;
		kabeD[1][0][1] = 1800;
		kabeD[1][1][0] = 240;
		kabeD[1][1][1] = 270;
		kabeD[2][0][0] = 1470;
		kabeD[2][0][1] = 1500;
		kabeD[2][1][0] = 180;
		kabeD[2][1][1] = 210;
		kabeD[3][0][0] = 1470;
		kabeD[3][0][1] = 1500;
		kabeD[3][1][0] = 240;
		kabeD[3][1][1] = 270;

		kuroikabe[0][0][0] = 1620;
		kuroikabe[0][0][1] = 1650;
		kuroikabe[0][1][0] = 210;
		kuroikabe[0][1][1] = 240;
		kuroikabe[1][0][0] = 1620;
		kuroikabe[1][0][1] = 1650;
		kuroikabe[1][1][0] = 270;
		kuroikabe[1][1][1] = 300;

		tannikabe[0][0][0] = 2085; tannikabe[0][0][1] = 2115; tannikabe[0][1][0] = 1000; tannikabe[0][1][1] = 1030;

		utimakuruteki[0][0] = 2100; utimakuruteki[0][1] = 330; utimakuruteki[0][3] = 240; utimakuruteki[0][5] = 500; utimakuruteki[0][10] = 100; utimakuruteki[0][11] = 30; utimakuruteki[0][14] = 15; utimakuruteki[0][15] = 20; utimakuruteki[0][16] = 1; utimakuruteki[0][17] = 1; utimakuruteki[0][28] = 1000;

		okaneaitemu[0][0] = 2100; okaneaitemu[0][1] = 650; okaneaitemu[0][2] = 100; okaneaitemu[0][3] = 1;
		kaihukuaitemu[0][0] = 2100; kaihukuaitemu[0][1] = 600; kaihukuaitemu[0][2] = 100; kaihukuaitemu[0][3] = 1;
	}
	if (genzainosutezi == 2) {
		kabeL[0][0][0] = 0;
		kabeL[0][0][1] = 670;
		kabeL[0][1][0] = 0;
		kabeL[0][1][1] = 30;
		kabeL[1][0][0] = 0;
		kabeL[1][0][1] = 30;
		kabeL[1][1][0] = 0;
		kabeL[1][1][1] = 480;
		kabeL[2][0][0] = 640;
		kabeL[2][0][1] = 670;
		kabeL[2][1][0] = -500;
		kabeL[2][1][1] = 610;
		kabeL[3][0][0] = -130;
		kabeL[3][0][1] = 670;
		kabeL[3][1][0] = 580;
		kabeL[3][1][1] = 610;
		kabeL[4][0][0] = -130;
		kabeL[4][0][1] = -100;
		kabeL[4][1][0] = -500;
		kabeL[4][1][1] = -180;
		kabeL[5][0][0] = -130;
		kabeL[5][0][1] = 670;
		kabeL[5][1][0] = -500;
		kabeL[5][1][1] = -470;
		kabeL[6][0][0] = 470;
		kabeL[6][0][1] = 500;
		kabeL[6][1][0] = -370;
		kabeL[6][1][1] = 0;
		kabeL[7][0][0] = 640;
		kabeL[7][0][1] = 670;
		kabeL[7][1][0] = -500;
		kabeL[7][1][1] = 610;
		kabeL[8][0][0] = -130;
		kabeL[8][0][1] = 670;
		kabeL[8][1][0] = 580;
		kabeL[8][1][1] = 610;
		kabeL[9][0][0] = -130;
		kabeL[9][0][1] = 670;
		kabeL[9][1][0] = -500;
		kabeL[9][1][1] = -470;
		//ここからダメージ壁
		kabeD[0][0][0] = 50;
		kabeD[0][0][1] = 200;
		kabeD[0][1][0] = 390;
		kabeD[0][1][1] = 450;
		kabeD[1][0][0] = 400;
		kabeD[1][0][1] = 430;
		kabeD[1][1][0] = 200;
		kabeD[1][1][1] = 330;
		kabeD[2][0][0] = 30;
		kabeD[2][0][1] = 430;
		kabeD[2][1][0] = 300;
		kabeD[2][1][1] = 330;
		kabeD[3][0][0] = 0;
		kabeD[3][0][1] = 30;
		kabeD[3][1][0] = -470;
		kabeD[3][1][1] = -440;
		kabeD[4][0][0] = 30;
		kabeD[4][0][1] = 60;
		kabeD[4][1][0] = -440;
		kabeD[4][1][1] = -410;
		kabeD[5][0][0] = 60;
		kabeD[5][0][1] = 90;
		kabeD[5][1][0] = -410;
		kabeD[5][1][1] = -380;
		kabeD[6][0][0] = 90;
		kabeD[6][0][1] = 120;
		kabeD[6][1][0] = -380;
		kabeD[6][1][1] = -350;
		kabeD[7][0][0] = 120;
		kabeD[7][0][1] = 150;
		kabeD[7][1][0] = -350;
		kabeD[7][1][1] = -320;
		kabeD[8][0][0] = 150;
		kabeD[8][0][1] = 180;
		kabeD[8][1][0] = -320;
		kabeD[8][1][1] = -290;
		kabeD[9][0][0] = 180;
		kabeD[9][0][1] = 210;
		kabeD[9][1][0] = -290;
		kabeD[9][1][1] = -260;

		//ここから黒い壁。
		kuroikabe[0][0][0] = -130;
		kuroikabe[0][0][1] = -100;
		kuroikabe[0][1][0] = -180;
		kuroikabe[0][1][1] = 580;
		
		//ここから集める壁。
		tannikabe[0][0][0] = 100;
		tannikabe[0][0][1] = 130;
		tannikabe[0][1][0] = 100;
		tannikabe[0][1][1] = 130;
		tannikabe[1][0][0] = 220;
		tannikabe[1][0][1] = 250;
		tannikabe[1][1][0] = -250;
		tannikabe[1][1][1] = -220;
		
		for (kurikaesi = 0; kurikaesi <= 3; kurikaesi++) {
			utimakuruteki[kurikaesi][0] = -180; utimakuruteki[kurikaesi][1] = -100+kurikaesi*120; utimakuruteki[kurikaesi][3] = 300; utimakuruteki[kurikaesi][5] = 200; utimakuruteki[kurikaesi][10] = 100; utimakuruteki[kurikaesi][11] = 30; utimakuruteki[kurikaesi][14] = 15; utimakuruteki[kurikaesi][15] = 10; utimakuruteki[kurikaesi][16] = 1; utimakuruteki[kurikaesi][28] = 1000;
		}
		zakoteki[0][0] = 640; zakoteki[0][1] = 320; zakoteki[0][3] = 0; zakoteki[0][4] = 0; zakoteki[0][5] = 200; zakoteki[0][7] = 15; zakoteki[0][8] = 100; zakoteki[0][9] = 120; zakoteki[0][10] = 0.05; zakoteki[0][11] = 3000;
		zakoteki[1][0] = 940; zakoteki[1][1] = 620; zakoteki[1][3] = 0; zakoteki[1][4] = 0; zakoteki[1][5] = 200; zakoteki[1][7] = 15; zakoteki[1][8] = 100; zakoteki[1][9] = 120; zakoteki[1][10] = 0.05; zakoteki[1][11] = 3000;
		ututeki[0][0] = 0; ututeki[0][1] = 320; ututeki[0][3] = 240; ututeki[0][5] = 400; ututeki[0][10] = 150; ututeki[0][11] = 20; ututeki[0][12] = 1; ututeki[0][13] = 40000; ututeki[0][14] = 8000; ututeki[0][15] = 10; ututeki[0][16] = 2; ututeki[0][17] = 1; ututeki[0][18] = 200;
		ututeki[1][0] = 0; ututeki[1][1] = 620; ututeki[1][3] = 240; ututeki[1][5] = 400; ututeki[1][10] = 150; ututeki[1][11] = 20; ututeki[1][12] = 1; ututeki[1][13] = 40000; ututeki[1][14] = 8000; ututeki[1][15] = 10; ututeki[1][16] = 2; ututeki[1][17] = 1; ututeki[1][18] = 200;
		okaneaitemu[0][0] = 600; okaneaitemu[0][1] = -185; okaneaitemu[0][2] = 100; okaneaitemu[0][3] = 1;
		okaneaitemu[1][0] = 540; okaneaitemu[1][1] = -185; okaneaitemu[1][2] = 100; okaneaitemu[1][3] = 1;
		okaneaitemu[2][0] = 600; okaneaitemu[2][1] = -105; okaneaitemu[2][2] = 100; okaneaitemu[2][3] = 1;
		okaneaitemu[3][0] = 540; okaneaitemu[3][1] = -105; okaneaitemu[3][2] = 100; okaneaitemu[3][3] = 1;
		kaihukuaitemu[0][0] = -55; kaihukuaitemu[0][1] = 300; kaihukuaitemu[0][2] = 100; kaihukuaitemu[0][3] = 1;

		//okaneaitemu[][0] = ; okaneaitemu[][1] = ; okaneaitemu[][2] = 300; okaneaitemu[][3] = 1;
		//kaihukuaitemu[][0] = ; kaihukuaitemu[][1] = ; kaihukuaitemu[][2] = ; kaihukuaitemu[][3] = ;
		//dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = ; dekaiteki[][7] = ; dekaiteki[][8] = ;
		//utimakuruteki[][0] = ; utimakuruteki[][1] = ; utimakuruteki[][3] = ; utimakuruteki[][5] = ; utimakuruteki[][10] = ; utimakuruteki[][11] = ; utimakuruteki[][14] = ; utimakuruteki[][15] = ; utimakuruteki[][16] = ; utimakuruteki[][28] = 1000;
		//ututeki[][0] = ; ututeki[][1] = ; ututeki[][3] = ; ututeki[][5] = 400; ututeki[][10] = ; ututeki[][11] = ; ututeki[][12] = ; ututeki[][13] = ; ututeki[][14] = ; ututeki[][15] = ; ututeki[][16] = ; ututeki[][17] = 1; ututeki[][18] = ;
		//zakoteki[][0] = ; zakoteki[][1] = ; zakoteki[0][3] = 0; zakoteki[0][4] = 0; zakoteki[0][5] = ; zakoteki[0][7] = 30; zakoteki[0][8] = ; zakoteki[0][9] = 240; zakoteki[0][10] = 0.02; zakoteki[0][11] = ;
		for (kurikaesi = 0; kurikaesi <= 7; kurikaesi++) {
			kabeDidou[kurikaesi] = 0;
		}
		kabeDidou1 = 0;
		//アイテムの個数の宣言
		k = 10;//壁の個数k個ある。
		n = 10;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 1;
		okaneaitemunokazu = 4;
		kaihukuaitemunokazu = 1;
		memonokazu = 0;
		tanninokazu = 2;
		tannihituyousuu = 2;
		zakotekinokazu = 2;
		ututekinokazu = 2;
		utimakurutekinokazu = 4;
		dekaitekinokazu = 0;
		damezikabenokougekiryoku = 10;
	}
	if (genzainosutezi == 3) {
		//ここからステージ3の壁の設定

		kabeL[0][0][0] = -30;
		kabeL[0][0][1] = 0;
		kabeL[0][1][0] = -110;
		kabeL[0][1][1] = 590;
		kabeL[1][0][0] = -30;
		kabeL[1][0][1] = 670;
		kabeL[1][1][0] = -110;
		kabeL[1][1][1] = -80;
		kabeL[2][0][0] = -30;
		kabeL[2][0][1] = 670;
		kabeL[2][1][0] = 560;
		kabeL[2][1][1] = 590;
		kabeL[3][0][0] = 640;
		kabeL[3][0][1] = 670;
		kabeL[3][1][0] = -110;
		kabeL[3][1][1] = 590;
		//ここからダメージ壁の設定
		kabeD[0][0][0] = 640;
		kabeD[0][0][1] = 720;
		kabeD[0][1][0] = -80;
		kabeD[0][1][1] = 0;
		kabeD[1][0][0] = 720;
		kabeD[1][0][1] = 800;
		kabeD[1][1][0] = 80;
		kabeD[1][1][1] = 160;
		kabeD[2][0][0] = 800;
		kabeD[2][0][1] = 880;
		kabeD[2][1][0] = 240;
		kabeD[2][1][1] = 320;
		kabeD[3][0][0] = 880;
		kabeD[3][0][1] = 960;
		kabeD[3][1][0] = 400;
		kabeD[3][1][1] = 480;
		kabeD[4][0][0] = 0;
		kabeD[4][0][1] = 80;
		kabeD[4][1][0] = -160 - 600;
		kabeD[4][1][1] = -80 - 600;
		kabeD[5][0][0] = 160;
		kabeD[5][0][1] = 240;
		kabeD[5][1][0] = -320 - 600;
		kabeD[5][1][1] = -240 - 600;
		kabeD[6][0][0] = 320;
		kabeD[6][0][1] = 400;
		kabeD[6][1][0] = -460 - 600;
		kabeD[6][1][1] = -380 - 600;
		kabeD[7][0][0] = 480;
		kabeD[7][0][1] = 560;
		kabeD[7][1][0] = -620 - 600;
		kabeD[7][1][1] = -540 - 600;
		kabeD[8][0][0] = -80 - 1200;
		kabeD[8][0][1] = 0 - 1200;
		kabeD[8][1][0] = 480;
		kabeD[8][1][1] = 560;
		kabeD[9][0][0] = -240 - 1200;
		kabeD[9][0][1] = -160 - 1200;
		kabeD[9][1][0] = 320;
		kabeD[9][1][1] = 400;
		kabeD[10][0][0] = -400 - 1200;
		kabeD[10][0][1] = -320 - 1200;
		kabeD[10][1][0] = 160;
		kabeD[10][1][1] = 240;
		kabeD[11][0][0] = -560 - 1200;
		kabeD[11][0][1] = -480 - 1200;
		kabeD[11][1][0] = 0;
		kabeD[11][1][1] = 80;
		kabeD[12][0][0] = 560;
		kabeD[12][0][1] = 640;
		kabeD[12][1][0] = 560 + 1800;
		kabeD[12][1][1] = 640 + 1800;
		kabeD[13][0][0] = 400;
		kabeD[13][0][1] = 480;
		kabeD[13][1][0] = 720 + 1800;
		kabeD[13][1][1] = 800 + 1800;
		kabeD[14][0][0] = 240;
		kabeD[14][0][1] = 320;
		kabeD[14][1][0] = 880 + 1800;
		kabeD[14][1][1] = 960 + 1800;
		kabeD[15][0][0] = 80;
		kabeD[15][0][1] = 160;
		kabeD[15][1][0] = 1040 + 1800;
		kabeD[15][1][1] = 1120 + 1800;

		//okaneaitemu[][0] = ; okaneaitemu[][1] = ; okaneaitemu[][2] = 300; okaneaitemu[][3] = 1;
		//kaihukuaitemu[][0] = ; kaihukuaitemu[][1] = ; kaihukuaitemu[][2] = ; kaihukuaitemu[][3] = ;
		//dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = ; dekaiteki[][7] = ; dekaiteki[][8] = ;
		//utimakuruteki[][0] = ; utimakuruteki[][1] = ; utimakuruteki[][3] = ; utimakuruteki[][5] = ; utimakuruteki[][10] = ; utimakuruteki[][11] = ; utimakuruteki[][14] = ; utimakuruteki[][15] = ; utimakuruteki[][16] = ; utimakuruteki[][28] = 1000;
		//ututeki[][0] = ; ututeki[][1] = ; ututeki[][3] = ; ututeki[][5] = 400; ututeki[][10] = ; ututeki[][11] = ; ututeki[][12] = ; ututeki[][13] = ; ututeki[][14] = ; ututeki[][15] = ; ututeki[][16] = ; ututeki[][17] = 1; ututeki[18][] = ;
		ututeki[0][0] = 640; ututeki[0][1] = -80; ututeki[0][3] = 180; ututeki[0][5] = 400; ututeki[0][10] = 50; ututeki[0][11] = 30; ututeki[0][12] = 1; ututeki[0][13] = 20000; ututeki[0][14] = 15000; ututeki[0][15] = 10; ututeki[0][16] = 3; ututeki[0][17] = 1; ututeki[0][18] = 1000;
		ututeki[1][0] = 720; ututeki[1][1] = 80; ututeki[1][3] = 180; ututeki[1][5] = 400; ututeki[1][10] = 50; ututeki[1][11] = 30; ututeki[1][12] = 1; ututeki[1][13] = 20000; ututeki[1][14] = 15000; ututeki[1][15] = 10; ututeki[1][16] = 3; ututeki[1][17] = 1; ututeki[1][18] = 1000;
		ututeki[2][0] = 800; ututeki[2][1] = 240; ututeki[2][3] = 180; ututeki[2][5] = 400; ututeki[2][10] = 50; ututeki[2][11] = 30; ututeki[2][12] = 1; ututeki[2][13] = 20000; ututeki[2][14] = 15000; ututeki[2][15] = 10; ututeki[2][16] = 3; ututeki[2][17] = 1; ututeki[2][18] = 1000;
		ututeki[3][0] = 880; ututeki[3][1] = 400; ututeki[3][3] = 180; ututeki[3][5] = 400; ututeki[3][10] = 50; ututeki[3][11] = 30; ututeki[3][12] = 1; ututeki[3][13] = 20000; ututeki[3][14] = 15000; ututeki[3][15] = 10; ututeki[3][16] = 3; ututeki[3][17] = 1; ututeki[3][18] = 1000;
		ututeki[4][0] = 0; ututeki[4][1] = -760; ututeki[4][3] = 180; ututeki[4][5] = 400; ututeki[4][10] = 50; ututeki[4][11] = 30; ututeki[4][12] = 1; ututeki[4][13] = 20000; ututeki[4][14] = 15000; ututeki[4][15] = 10; ututeki[4][16] = 3; ututeki[4][17] = 1; ututeki[4][18] = 1000;
		ututeki[5][0] = 160; ututeki[5][1] = -840; ututeki[5][3] = 180; ututeki[5][5] = 400; ututeki[5][10] = 50; ututeki[5][11] = 30; ututeki[5][12] =1 ; ututeki[5][13] = 20000; ututeki[5][14] = 15000; ututeki[5][15] = 10; ututeki[5][16] = 3; ututeki[5][17] = 1; ututeki[5][18] = 1000;
		ututeki[6][0] = 320; ututeki[6][1] = -920; ututeki[6][3] = 180; ututeki[6][5] = 400; ututeki[6][10] = 50; ututeki[6][11] = 30; ututeki[6][12] = 1; ututeki[6][13] = 20000; ututeki[6][14] = 15000; ututeki[6][15] = 10; ututeki[6][16] = 3; ututeki[6][17] = 1; ututeki[6][18] = 1000;
		ututeki[7][0] = 480; ututeki[7][1] = -1000; ututeki[7][3] = 180; ututeki[7][5] = 400; ututeki[7][10] = 50; ututeki[7][11] = 30; ututeki[7][12] = 1; ututeki[7][13] = 20000; ututeki[7][14] = 15000; ututeki[7][15] = 10; ututeki[7][16] = 3; ututeki[7][17] = 1; ututeki[7][18] = 1000;
		ututeki[8][0] = -1200; ututeki[8][1] = 480; ututeki[8][3] = 180; ututeki[8][5] = 400; ututeki[8][10] = 50; ututeki[8][11] = 30; ututeki[8][12] = 1; ututeki[8][13] = 20000; ututeki[8][14] = 15000; ututeki[8][15] = 10; ututeki[8][16] = 3; ututeki[8][17] = 1; ututeki[8][18] = 1000;
		ututeki[9][0] = -1260; ututeki[9][1] = 320; ututeki[9][3] = 180; ututeki[9][5] = 400; ututeki[9][10] = 50; ututeki[9][11] = 30; ututeki[9][12] = 1; ututeki[9][13] = 20000; ututeki[9][14] = 15000; ututeki[9][15] = 10; ututeki[9][16] = 3; ututeki[9][17] = 1; ututeki[9][18] = 1000;
		ututeki[10][0] = -1320; ututeki[10][1] = 160; ututeki[10][3] = 180; ututeki[10][5] = 400; ututeki[10][10] = 50; ututeki[10][11] = 30; ututeki[10][12] = 1; ututeki[10][13] = 20000; ututeki[10][14] = 15000; ututeki[10][15] = 10; ututeki[10][16] = 3; ututeki[10][17] = 1; ututeki[10][18] = 1000;
		ututeki[11][0] = -1380; ututeki[11][1] = 0; ututeki[11][3] = 180; ututeki[11][5] = 400; ututeki[11][10] = 50; ututeki[11][11] = 30; ututeki[11][12] = 1; ututeki[11][13] = 20000; ututeki[11][14] = 15000; ututeki[11][15] = 10; ututeki[11][16] = 3; ututeki[11][17] = 1; ututeki[11][18] = 1000;
		ututeki[12][0] = 560; ututeki[12][1] = 2360; ututeki[12][3] = 180; ututeki[12][5] = 400; ututeki[12][10] = 50; ututeki[12][11] = 30; ututeki[12][12] = 1; ututeki[12][13] = 20000; ututeki[12][14] = 15000; ututeki[12][15] = 10; ututeki[12][16] = 3; ututeki[12][17] = 1; ututeki[12][18] = 1000;
		ututeki[13][0] = 400; ututeki[13][1] = 2420; ututeki[13][3] = 180; ututeki[13][5] = 400; ututeki[13][10] = 50; ututeki[13][11] = 30; ututeki[13][12] = 1; ututeki[13][13] = 20000; ututeki[13][14] = 15000; ututeki[13][15] = 10; ututeki[13][16] = 3; ututeki[13][17] = 1; ututeki[13][18] = 1000;
		ututeki[14][0] = 240; ututeki[14][1] = 2480; ututeki[14][3] = 180; ututeki[14][5] = 400; ututeki[14][10] = 50; ututeki[14][11] = 30; ututeki[14][12] = 1; ututeki[14][13] = 20000; ututeki[14][14] = 15000; ututeki[14][15] = 10; ututeki[14][16] = 3; ututeki[14][17] = 1; ututeki[14][18] = 1000;
		ututeki[15][0] = 80; ututeki[15][1] = 2560; ututeki[15][3] = 180; ututeki[15][5] = 400; ututeki[15][10] = 50; ututeki[15][11] = 30; ututeki[15][12] = 1; ututeki[15][13] = 20000; ututeki[15][14] = 15000; ututeki[15][15] = 10; ututeki[15][16] = 3; ututeki[15][17] = 1; ututeki[15][18] = 1000;
		
		okaneaitemu[0][0] = 160; okaneaitemu[0][1] = 80; okaneaitemu[0][2] = 50; okaneaitemu[0][3] = 1;
		okaneaitemu[1][0] = 480; okaneaitemu[1][1] = 400; okaneaitemu[1][2] = 50; okaneaitemu[1][3] = 1;
		okaneaitemu[2][0] = 480; okaneaitemu[2][1] = 80; okaneaitemu[2][2] = 50; okaneaitemu[2][3] = 1;
		okaneaitemu[3][0] = 160; okaneaitemu[3][1] = 400; okaneaitemu[3][2] = 50; okaneaitemu[3][3] = 1;
		
		kaihukuaitemu[0][0] = 240; kaihukuaitemu[0][1] = 160; kaihukuaitemu[0][2] = 100; kaihukuaitemu[0][3] = 1;
		kaihukuaitemu[1][0] = 400; kaihukuaitemu[1][1] = 320; kaihukuaitemu[1][2] = 100; kaihukuaitemu[1][3] = 1;
		kaihukuaitemu[2][0] = 240; kaihukuaitemu[2][1] = 320; kaihukuaitemu[2][2] = 100; kaihukuaitemu[2][3] = 1;
		kaihukuaitemu[3][0] = 400; kaihukuaitemu[3][1] = 160; kaihukuaitemu[3][2] = 100; kaihukuaitemu[3][3] = 1;
		
		dekaiteki[0][0] = 320; dekaiteki[0][1] = 80; dekaiteki[0][5] = 500; dekaiteki[0][7] = 30; dekaiteki[0][8] = 50;
		dekaiteki[1][0] = 160; dekaiteki[1][1] = 240; dekaiteki[1][5] = 500; dekaiteki[1][7] = 30; dekaiteki[1][8] = 50;
		dekaiteki[2][0] = 480; dekaiteki[2][1] = 240; dekaiteki[2][5] = 500; dekaiteki[2][7] = 30; dekaiteki[2][8] = 50;
		dekaiteki[3][0] = 320; dekaiteki[3][1] = 400; dekaiteki[3][5] = 500; dekaiteki[3][7] = 30; dekaiteki[3][8] = 50;
		
		utimakuruteki[0][0] = 80; utimakuruteki[0][1] = 240; utimakuruteki[0][3] = 300; utimakuruteki[0][5] = 360; utimakuruteki[0][10] = 100; utimakuruteki[0][11] = 30; utimakuruteki[0][14] = 15; utimakuruteki[0][15] = 10; utimakuruteki[0][16] = 2; utimakuruteki[0][17] = 1; utimakuruteki[0][28] = 1000;
		utimakuruteki[1][0] = 320; utimakuruteki[1][1] = 480; utimakuruteki[1][3] = 300; utimakuruteki[1][5] = 360; utimakuruteki[1][10] = 100; utimakuruteki[1][11] = 30; utimakuruteki[1][14] = 15; utimakuruteki[1][15] = 10; utimakuruteki[1][16] = 2; utimakuruteki[1][17] = 91; utimakuruteki[1][28] = 1000;
		utimakuruteki[2][0] = 560; utimakuruteki[2][1] = 240; utimakuruteki[2][3] = 300; utimakuruteki[2][5] = 360; utimakuruteki[2][10] = 100; utimakuruteki[2][11] = 30; utimakuruteki[2][14] = 15; utimakuruteki[2][15] = 10; utimakuruteki[2][16] = 2; utimakuruteki[2][17] = 181; utimakuruteki[2][28] = 1000;
		utimakuruteki[3][0] = 320; utimakuruteki[3][1] = 0; utimakuruteki[3][3] = 300; utimakuruteki[3][5] = 360; utimakuruteki[3][10] = 100; utimakuruteki[3][11] = 30; utimakuruteki[3][14] = 15; utimakuruteki[3][15] = 10; utimakuruteki[3][16] = 2; utimakuruteki[3][17] = 271; utimakuruteki[3][28] = 1000;
		
		tannikabe[0][0][0] = 305; tannikabe[0][0][1] = 335; tannikabe[0][1][0] = 225-4600; tannikabe[0][1][1] = 255-4600;
		
		zakoteki[0][0] = 320+3000; zakoteki[0][1] = 240; zakoteki[0][3] = 0; zakoteki[0][4] = 0; zakoteki[0][5] = 500; zakoteki[0][7] = 15; zakoteki[0][8] = 100; zakoteki[0][9] = 240; zakoteki[0][10] = 0.02; zakoteki[0][11] = 3000;
		zakoteki[1][0] = 320+5000; zakoteki[1][1] = 240; zakoteki[1][3] = 0; zakoteki[1][4] = 0; zakoteki[1][5] = 500; zakoteki[1][7] = 15; zakoteki[1][8] = 100; zakoteki[1][9] = 240; zakoteki[1][10] = 0.02; zakoteki[1][11] = 3000;
		zakoteki[2][0] = 320+4000; zakoteki[2][1] = 240; zakoteki[2][3] = 0; zakoteki[2][4] = 0; zakoteki[2][5] = 500; zakoteki[2][7] = 15; zakoteki[2][8] = 100; zakoteki[2][9] = 240; zakoteki[2][10] = 0.02; zakoteki[2][11] = 3000;
		zakoteki[3][0] = 320+6000; zakoteki[3][1] = 240; zakoteki[3][3] = 0; zakoteki[3][4] = 0; zakoteki[3][5] = 500; zakoteki[3][7] = 15; zakoteki[3][8] = 100; zakoteki[3][9] = 240; zakoteki[3][10] = 0.02; zakoteki[3][11] = 3000;
		zakoteki[4][0] = 320; zakoteki[4][1] = 240+3000; zakoteki[4][3] = 0; zakoteki[4][4] = 0; zakoteki[4][5] = 500; zakoteki[4][7] = 15; zakoteki[4][8] = 100; zakoteki[4][9] = 240; zakoteki[4][10] = 0.02; zakoteki[4][11] = 3000;
		zakoteki[5][0] = 320; zakoteki[5][1] = 240+4000; zakoteki[5][3] = 0; zakoteki[5][4] = 0; zakoteki[5][5] = 500; zakoteki[5][7] = 15; zakoteki[5][8] = 100; zakoteki[5][9] = 240; zakoteki[5][10] = 0.02; zakoteki[5][11] = 3000;
		zakoteki[6][0] = 320; zakoteki[6][1] = 240+5000; zakoteki[6][3] = 0; zakoteki[6][4] = 0; zakoteki[6][5] = 500; zakoteki[6][7] = 15; zakoteki[6][8] = 100; zakoteki[6][9] = 240; zakoteki[6][10] = 0.02; zakoteki[6][11] = 3000;
		zakoteki[7][0] = 320; zakoteki[7][1] = 240+6000; zakoteki[7][3] = 0; zakoteki[7][4] = 0; zakoteki[7][5] = 500; zakoteki[7][7] = 15; zakoteki[7][8] = 100; zakoteki[7][9] = 240; zakoteki[7][10] = 0.02; zakoteki[7][11] = 3000;
		zakoteki[8][0] = 320-3000; zakoteki[8][1] = 240; zakoteki[8][3] = 0; zakoteki[8][4] = 0; zakoteki[8][5] = 500; zakoteki[8][7] = 15; zakoteki[8][8] = 100; zakoteki[8][9] = 240; zakoteki[8][10] = 0.02; zakoteki[8][11] = 3000;
		zakoteki[9][0] = 320-4000; zakoteki[9][1] = 240; zakoteki[9][3] = 0; zakoteki[9][4] = 0; zakoteki[9][5] = 500; zakoteki[9][7] = 15; zakoteki[9][8] = 100; zakoteki[9][9] = 240; zakoteki[9][10] = 0.02; zakoteki[9][11] = 3000;
		zakoteki[10][0] = 320-5000; zakoteki[10][1] = 240; zakoteki[10][3] = 0; zakoteki[10][4] = 0; zakoteki[10][5] = 500; zakoteki[10][7] = 15; zakoteki[10][8] = 100; zakoteki[10][9] = 240; zakoteki[10][10] = 0.02; zakoteki[10][11] = 3000;
		zakoteki[11][0] = 320-6000; zakoteki[11][1] = 240; zakoteki[11][3] = 0; zakoteki[11][4] = 0; zakoteki[11][5] = 500; zakoteki[11][7] = 15; zakoteki[11][8] = 100; zakoteki[11][9] = 240; zakoteki[11][10] = 0.02; zakoteki[11][11] = 3000;
		zakoteki[12][0] = 320; zakoteki[12][1] = 240-3000; zakoteki[12][3] = 0; zakoteki[12][4] = 0; zakoteki[12][5] = 500; zakoteki[12][7] = 15; zakoteki[12][8] = 100; zakoteki[12][9] = 240; zakoteki[12][10] = 0.02; zakoteki[12][11] = 3000;
		zakoteki[13][0] = 320; zakoteki[13][1] = 240-4000; zakoteki[13][3] = 0; zakoteki[13][4] = 0; zakoteki[13][5] = 500; zakoteki[13][7] = 15; zakoteki[13][8] = 100; zakoteki[13][9] = 240; zakoteki[13][10] = 0.02; zakoteki[13][11] = 3000;
		zakoteki[14][0] = 320; zakoteki[14][1] = 240-5000; zakoteki[14][3] = 0; zakoteki[14][4] = 0; zakoteki[14][5] = 500; zakoteki[14][7] = 15; zakoteki[14][8] = 100; zakoteki[14][9] = 240; zakoteki[14][10] = 0.02; zakoteki[14][11] = 3000;
		zakoteki[15][0] = 320; zakoteki[15][1] = 240-6000; zakoteki[15][3] = 0; zakoteki[15][4] = 0; zakoteki[15][5] = 500; zakoteki[15][7] = 15; zakoteki[15][8] = 100; zakoteki[15][9] = 240; zakoteki[15][10] = 0.02; zakoteki[15][11] = 3000;

		//アイテムの個数の宣言
		k = 4;//壁の個数k個ある。
		n = 16;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 4;
		kaihukuaitemunokazu = 4;
		memonokazu = 0;
		tanninokazu = 1;
		tannihituyousuu = 1;
		zakotekinokazu = 16;
		ututekinokazu = 16;
		utimakurutekinokazu = 4;
		dekaitekinokazu = 4;
		damezikabenokougekiryoku = 30;
		
		
	}
	
	if (genzainosutezi == 7) {
		

		kabeL[0][0][0] = 240;
		kabeL[0][0][1] = 250;
		kabeL[0][1][0] = 0;
		kabeL[0][1][1] = 490;
		kabeL[1][0][0] = 240;
		kabeL[1][0][1] = 3730;
		kabeL[1][1][0] = 0;
		kabeL[1][1][1] = 10;
		kabeL[2][0][0] = 240;
		kabeL[2][0][1] = 3730;
		kabeL[2][1][0] = 480;
		kabeL[2][1][1] = 490;
		kabeL[3][0][0] = 3720;
		kabeL[3][0][1] = 3730;
		kabeL[3][1][0] =  0;
		kabeL[3][1][1] = 480;
		/*
		kabeD[0][0][0] = 640;
		kabeD[0][0][1] = 720;
		kabeD[0][1][0] = -80;
		kabeD[0][1][1] = 0;
		*/
		/*
		for (kurikaesi = 0; kurikaesi < 9; kurikaesi++) {
			kabeD[kurikaesi][0][0] = 1000;
			kabeD[kurikaesi][0][1] = 1030;
			kabeD[kurikaesi][1][0] = 10+kurikaesi*50;
			kabeD[kurikaesi][1][1] = 40+kurikaesi*50;
		}
		for (kurikaesi = 9; kurikaesi < 18; kurikaesi++) {
			kabeD[kurikaesi][0][0] = 1500;
			kabeD[kurikaesi][0][1] = 1530;
			kabeD[kurikaesi][1][0] = 40 + (kurikaesi-9) * 50;
			kabeD[kurikaesi][1][1] = 70 + (kurikaesi-9) * 50;
		}
		for (kurikaesi = 18; kurikaesi < 27; kurikaesi++) {
			kabeD[kurikaesi][0][0] = 2000;
			kabeD[kurikaesi][0][1] = 2030;
			kabeD[kurikaesi][1][0] = 10 + (kurikaesi - 18) * 50;
			kabeD[kurikaesi][1][1] = 40 + (kurikaesi - 18) * 50;
		}
		*/
		/*
		for (kurikaesi = 0; kurikaesi <= 3; kurikaesi++) {
			kabeL[kurikaesi][0][0] = 2300+(kurikaesi)*140;
			kabeL[kurikaesi][0][1] = 2310 + (kurikaesi) * 140;
			kabeL[kurikaesi][1][0] = 10;
			kabeL[kurikaesi][1][1] = 410;
		}
		*/
		/*
		for (kurikaesi = 4; kurikaesi <= 7; kurikaesi++) {
			kabeL[kurikaesi][0][0] = 2370 + (kurikaesi) * 140;
			kabeL[kurikaesi][0][1] = 2380 + (kurikaesi) * 140;
			kabeL[kurikaesi][1][0] = 70;
			kabeL[kurikaesi][1][1] = 470;
		}*/
		/*
		for (kurikaesi = 8; kurikaesi <= 11; kurikaesi++) {
			kuroikabe[kurikaesi][0][0] = 3200;
			kuroikabe[kurikaesi][0][1] = 3300;
			kuroikabe[kurikaesi][1][0] = 10 + (kurikaesi-8) * 100;
			kuroikabe[kurikaesi][1][1] = 110 + (kurikaesi-8) * 100;
		}*/
		for (kurikaesi = 0; kurikaesi < 100; kurikaesi++) {
			zakoteki[kurikaesi][0] = 200-kurikaesi*50; zakoteki[kurikaesi][1] = 240; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0;
			zakoteki[kurikaesi][5] = 1000; zakoteki[kurikaesi][7] = 25; zakoteki[kurikaesi][8] = 150; zakoteki[kurikaesi][9] = 180; zakoteki[kurikaesi][10] = 0.03; zakoteki[kurikaesi][11] = 6000;
		}
		/*
		for (kurikaesi = 0; kurikaesi < 9; kurikaesi++) {
			zakoteki[kurikaesi][0] = -100; zakoteki[kurikaesi][1] = kurikaesi * 60; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0;
			zakoteki[kurikaesi][5] = 300; zakoteki[kurikaesi][7] = 25; zakoteki[kurikaesi][8] = 150; zakoteki[kurikaesi][9] = 90; zakoteki[kurikaesi][10] = 0.05; zakoteki[kurikaesi][11] = 4500;
		}
		*/
		/*
		for (kurikaesi = 9; kurikaesi < 16; kurikaesi++) {
			zakoteki[kurikaesi][0] = -600; zakoteki[kurikaesi][1] = kurikaesi * 60; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0;
			zakoteki[kurikaesi][5] = 300; zakoteki[kurikaesi][7] = 25; zakoteki[kurikaesi][8] = 150; zakoteki[kurikaesi][9] = 90; zakoteki[kurikaesi][10] = 0.05; zakoteki[kurikaesi][11] = 4500;
		}
		*/
		/* (kurikaesi = 9; kurikaesi < 16; kurikaesi++) {
		utimakuruteki[0][0] = 95; utimakuruteki[0][1] = -15; utimakuruteki[0][3] = 450; utimakuruteki[0][5] = 800; utimakuruteki[0][10] = 150; utimakuruteki[0][11] = 30; utimakuruteki[0][14] = 5; utimakuruteki[0][15] = 10; utimakuruteki[0][16] = 3; utimakuruteki[0][17] = 1; utimakuruteki[0][28] = 1000;
		}*/
		
		for (kurikaesi = 0; kurikaesi <= 7; kurikaesi++) {
			dekaiteki[kurikaesi][0] = 500; dekaiteki[kurikaesi][1] = kurikaesi*59+40; dekaiteki[kurikaesi][5] = 500; dekaiteki[kurikaesi][7] = 50; dekaiteki[kurikaesi][8] = 50;
		}
		for (kurikaesi = 8; kurikaesi <= 11; kurikaesi++) {
			dekaiteki[kurikaesi][0] = 800; dekaiteki[kurikaesi][1] = (kurikaesi-8) * 120 + 30; dekaiteki[kurikaesi][5] = 500; dekaiteki[kurikaesi][7] = 50; dekaiteki[kurikaesi][8] = 50;
		}
		for (kurikaesi = 12; kurikaesi <= 15; kurikaesi++) {
			dekaiteki[kurikaesi][0] = 920; dekaiteki[kurikaesi][1] = (kurikaesi - 12) * 120 + 90; dekaiteki[kurikaesi][5] = 500; dekaiteki[kurikaesi][7] = 50; dekaiteki[kurikaesi][8] = 50;
		}
		for (kurikaesi = 16; kurikaesi <= 19; kurikaesi++) {
			dekaiteki[kurikaesi][0] = 1040; dekaiteki[kurikaesi][1] = (kurikaesi - 16) * 120 + 30; dekaiteki[kurikaesi][5] = 500; dekaiteki[kurikaesi][7] = 50; dekaiteki[kurikaesi][8] = 50;
		}
		tannikabe[4][0][0] = 845;
		tannikabe[4][0][1] = 875;
		tannikabe[4][1][0] = 230;
		tannikabe[4][1][1] = 260;
		tannikabe[5][0][0] = 1195;
		tannikabe[5][0][1] = 1225;
		tannikabe[5][1][0] = 15;
		tannikabe[5][1][1] = 45;
		tannikabe[6][0][0] = 1195;
		tannikabe[6][0][1] = 1225;
		tannikabe[6][1][0] = 445;
		tannikabe[6][1][1] = 475;
		for (kurikaesi = 0; kurikaesi <= 7; kurikaesi++) {
			utimakuruteki[kurikaesi][0] = 1670; utimakuruteki[kurikaesi][1] = kurikaesi*60+20; utimakuruteki[kurikaesi][3] = 160; utimakuruteki[kurikaesi][5] = 400; utimakuruteki[kurikaesi][10] = 300; utimakuruteki[kurikaesi][11] = 50; utimakuruteki[kurikaesi][14] = 5; utimakuruteki[kurikaesi][15] = 10; utimakuruteki[kurikaesi][16] = 3; utimakuruteki[kurikaesi][17] = kurikaesi*40-160; utimakuruteki[kurikaesi][28] = 0;
		}
		for (kurikaesi = 8; kurikaesi <= 15; kurikaesi++) {
			utimakuruteki[kurikaesi][0] = 2270; utimakuruteki[kurikaesi][1] = (kurikaesi-8) * 60 + 50; utimakuruteki[kurikaesi][3] = 160; utimakuruteki[kurikaesi][5] = 400; utimakuruteki[kurikaesi][10] = 300; utimakuruteki[kurikaesi][11] = 50; utimakuruteki[kurikaesi][14] = 5; utimakuruteki[kurikaesi][15] = 10; utimakuruteki[kurikaesi][16] = 3; utimakuruteki[kurikaesi][17] = (kurikaesi-8) * 40-180; utimakuruteki[kurikaesi][28] = 0;
		}
		tannikabe[0][0][0] = 1700;
		tannikabe[0][0][1] = 1730;
		tannikabe[0][1][0] = 40;
		tannikabe[0][1][1] = 70;
		tannikabe[1][0][0] = 2100;
		tannikabe[1][0][1] = 2130;
		tannikabe[1][1][0] = 440;
		tannikabe[1][1][1] = 470;
		tannikabe[2][0][0] = 1700;
		tannikabe[2][0][1] = 1730;
		tannikabe[2][1][0] = 440;
		tannikabe[2][1][1] = 470;
		tannikabe[3][0][0] = 2100;
		tannikabe[3][0][1] = 2130;
		tannikabe[3][1][0] = 40;
		tannikabe[3][1][1] = 70;
		for (kurikaesi = 4; kurikaesi <= 7; kurikaesi++) {
			kabeL[kurikaesi][0][0] = 770;
			kabeL[kurikaesi][0][1] = 830;
			kabeL[kurikaesi][1][0] = 60 + (kurikaesi - 4) * 120;
			kabeL[kurikaesi][1][1] = 120 + (kurikaesi - 4) * 120;
		}
		for (kurikaesi = 8; kurikaesi <= 11; kurikaesi++) {
			kabeL[kurikaesi][0][0] = 890;
			kabeL[kurikaesi][0][1] = 950;
			kabeL[kurikaesi][1][0] = 0 + (kurikaesi - 8) * 120;
			kabeL[kurikaesi][1][1] = 60 + (kurikaesi - 8) * 120;
		}
		for (kurikaesi = 12; kurikaesi <= 15; kurikaesi++) {
			kabeL[kurikaesi][0][0] = 1010;
			kabeL[kurikaesi][0][1] = 1070;
			kabeL[kurikaesi][1][0] = 60 + (kurikaesi - 12) * 120;
			kabeL[kurikaesi][1][1] = 120 + (kurikaesi - 12) * 120;
		}
		kabeL[16][0][0] = 1130;
		kabeL[16][0][1] = 1190;
		kabeL[16][1][0] = 10;
		kabeL[16][1][1] = 220;
		kabeL[17][0][0] = 1130;
		kabeL[17][0][1] = 1190;
		kabeL[17][1][0] = 280;
		kabeL[17][1][1] = 490;
		okaneaitemu[0][0] = 1135; okaneaitemu[0][1] = 225; okaneaitemu[0][2] = 150; okaneaitemu[0][3] = 1;
		okaneaitemu[1][0] = 1135; okaneaitemu[1][1] = 275; okaneaitemu[1][2] = 150; okaneaitemu[1][3] = 1;
		okaneaitemu[2][0] = 1185; okaneaitemu[2][1] = 225; okaneaitemu[2][2] = 150; okaneaitemu[2][3] = 1;
		okaneaitemu[3][0] = 1185; okaneaitemu[3][1] = 275; okaneaitemu[3][2] = 150; okaneaitemu[3][3] = 1;

		kabeL[18][0][0] = 2570;
		kabeL[18][0][1] = 3720;
		kabeL[18][1][0] = 10;
		kabeL[18][1][1] = 210;
		kabeL[19][0][0] = 2570;
		kabeL[19][0][1] = 3720;
		kabeL[19][1][0] = 280;
		kabeL[19][1][1] = 490;
		for (kurikaesi = 20; kurikaesi <= 29; kurikaesi++) {
			dekaiteki[kurikaesi][0] = 2600+(kurikaesi-20)*90; dekaiteki[kurikaesi][1] = 240; dekaiteki[kurikaesi][5] = 500+(kurikaesi-20)*100; dekaiteki[kurikaesi][7] = 100; dekaiteki[kurikaesi][8] = 50;
		}
		for (kurikaesi = 4; kurikaesi <= 15; kurikaesi++) {
			okaneaitemu[kurikaesi][0] = 2645 + (kurikaesi-4) * 90; okaneaitemu[kurikaesi][1] = 240; okaneaitemu[kurikaesi][2] = 300+(kurikaesi*300); okaneaitemu[kurikaesi][3] = 1;
		}
		
		/*
		dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = 500; dekaiteki[][7] = 50; dekaiteki[][8] = 50;
		dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = 500; dekaiteki[][7] = 50; dekaiteki[][8] = 50;
		dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = 500; dekaiteki[][7] = 50; dekaiteki[][8] = 50;
		*/
		
		
		//kaihukuaitemu[][0] = ; kaihukuaitemu[][1] = ; kaihukuaitemu[][2] = ; kaihukuaitemu[][3] = ;
		//dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = ; dekaiteki[][7] = ; dekaiteki[][8] = ;
		//utimakuruteki[][0] = ; utimakuruteki[][1] = ; utimakuruteki[][3] = ; utimakuruteki[][5] = ; utimakuruteki[][10] = ; utimakuruteki[][11] = ; utimakuruteki[][14] = ; utimakuruteki[][15] = ; utimakuruteki[][16] = ; utimakuruteki[][28] = 1000;
		//ututeki[][0] = ; ututeki[][1] = ; ututeki[][3] = ; ututeki[][5] = 400; ututeki[][10] = ; ututeki[][11] = ; ututeki[][12] = ; ututeki[][13] = ; ututeki[][14] = ; ututeki[][15] = ; ututeki[][16] = ; ututeki[][17] = 1; ututeki[18][] = ;
		
		
		//アイテムの個数の宣言
		k = 20;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 16;
		kaihukuaitemunokazu = 0;
		memonokazu = 0;
		tanninokazu = 7;
		tannihituyousuu = 7;
		zakotekinokazu = 100;
		ututekinokazu = 0;
		utimakurutekinokazu = 16;
		dekaitekinokazu = 30;
	}
	if (genzainosutezi == 5) {
		//ここからステージ5の壁の設定
		kuroikabe[0][0][0] = 300;
		kuroikabe[0][0][1] = 310;
		kuroikabe[0][1][0] = 0;
		kuroikabe[0][1][1] = 480;
		kuroikabe[1][0][0] = 330;
		kuroikabe[1][0][1] = 340;
		kuroikabe[1][1][0] = 0;
		kuroikabe[1][1][1] = 480;
		kuroikabe[2][0][0] = 300;
		kuroikabe[2][0][1] = 340;
		kuroikabe[2][1][0] = 0;
		kuroikabe[2][1][1] = 10;
		kuroikabe[3][0][0] = 300;
		kuroikabe[3][0][1] = 340;
		kuroikabe[3][1][0] = 470;
		kuroikabe[3][1][1] = 480;
		tannikabe[0][0][0] = 305; tannikabe[0][0][1] = 335; tannikabe[0][1][0] = -2630; tannikabe[0][1][1] = -2600;

		//kaihukuaitemu[][0] = ; kaihukuaitemu[][1] = ; kaihukuaitemu[][2] = ; kaihukuaitemu[][3] = ;
		//dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = ; dekaiteki[][7] = ; dekaiteki[][8] = ;
		//utimakuruteki[][0] = ; utimakuruteki[][1] = ; utimakuruteki[][3] = ; utimakuruteki[][5] = ; utimakuruteki[][10] = ; utimakuruteki[][11] = ; utimakuruteki[][14] = ; utimakuruteki[][15] = ; utimakuruteki[][16] = ; utimakuruteki[][28] = 1000;
		//ututeki[][0] = ; ututeki[][1] = ; ututeki[][3] = ; ututeki[][5] = 400; ututeki[][10] = ; ututeki[][11] = ; ututeki[][12] = ; ututeki[][13] = ; ututeki[][14] = ; ututeki[][15] = ; ututeki[][16] = ; ututeki[][17] = 1; ututeki[][18] = ;
		//zakoteki[][0] = ; zakoteki[][1] = ; zakoteki[0][3] = 0; zakoteki[0][4] = 0; zakoteki[0][5] = ; zakoteki[0][7] = 30; zakoteki[0][8] = ; zakoteki[0][9] = 240; zakoteki[0][10] = 0.02; zakoteki[0][11] = ;

		for (kurikaesi = 0; kurikaesi <= 14; kurikaesi++) {
			ututeki[kurikaesi][0] = 320-kurikaesi*75-300; ututeki[kurikaesi][1] = 480-kurikaesi*40; ututeki[kurikaesi][3] = 180; ututeki[kurikaesi][5] = 130; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 0.5; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 10; ututeki[kurikaesi][16] = 2; ututeki[kurikaesi][17] = 1; ututeki[kurikaesi][18] = 3000;
		}
		for (kurikaesi = 15; kurikaesi <= 29; kurikaesi++) {
			ututeki[kurikaesi][0] = 320 + (kurikaesi-15) * 75 + 300; ututeki[kurikaesi][1] = 0 + (kurikaesi-15) *40; ututeki[kurikaesi][3] = 180; ututeki[kurikaesi][5] = 130; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 0.5; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 10; ututeki[kurikaesi][16] = 2; ututeki[kurikaesi][17] = 1; ututeki[kurikaesi][18] = 3000;
		}
		
		for (kurikaesi = 0; kurikaesi <= 14; kurikaesi++) {
			zakoteki[kurikaesi][0] = 320; zakoteki[kurikaesi][1] = -kurikaesi*60-100; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0; zakoteki[kurikaesi][5] = 150; zakoteki[kurikaesi][7] = 30; zakoteki[kurikaesi][8] = 30; zakoteki[kurikaesi][9] = 30; zakoteki[kurikaesi][10] = 0.04; zakoteki[kurikaesi][11] = 0;
		}
		for (kurikaesi = 15; kurikaesi <= 29; kurikaesi++) {
			zakoteki[kurikaesi][0] = 320; zakoteki[kurikaesi][1] = (kurikaesi-15) * 60+580; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0; zakoteki[kurikaesi][5] = 150; zakoteki[kurikaesi][7] = 30; zakoteki[kurikaesi][8] = 30; zakoteki[kurikaesi][9] = 30; zakoteki[kurikaesi][10] = 0.04; zakoteki[kurikaesi][11] = 0;
		}
		//アイテムの個数の宣言
		k = 0;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 4;
		okaneaitemunokazu = 0;
		kaihukuaitemunokazu = 0;
		memonokazu = 0;
		tanninokazu = 1;
		tannihituyousuu = 1;
		zakotekinokazu = 30;
		ututekinokazu = 30;
		utimakurutekinokazu = 0;
		dekaitekinokazu = 0;
	}
	
	if (genzainosutezi == 6) {
		//ここからステージ6の壁の設定

		kabeL[0][0][0] = 40;
		kabeL[0][0][1] = 50;
		kabeL[0][1][0] = -40;
		kabeL[0][1][1] = 530;
		kabeL[1][0][0] = 40;
		kabeL[1][0][1] = 610;
		kabeL[1][1][0] = -40;
		kabeL[1][1][1] = -30;
		kabeL[2][0][0] = 40;
		kabeL[2][0][1] = 610;
		kabeL[2][1][0] = 520;
		kabeL[2][1][1] = 530;
		kabeL[3][0][0] = 80;
		kabeL[3][0][1] = 90;
		kabeL[3][1][0] = 0;
		kabeL[3][1][1] = 230;
		kabeL[4][0][0] = 80;
		kabeL[4][0][1] = 90;
		kabeL[4][1][0] = 250;
		kabeL[4][1][1] = 490;
		kabeL[5][0][0] = 80;
		kabeL[5][0][1] = 310;
		kabeL[5][1][0] = 0;
		kabeL[5][1][1] = 10;
		kabeL[6][0][0] = 80;
		kabeL[6][0][1] = 310;
		kabeL[6][1][0] = 480;
		kabeL[6][1][1] = 490;
		kabeL[7][0][0] = 330;
		kabeL[7][0][1] = 570;
		kabeL[7][1][0] = 0;
		kabeL[7][1][1] = 10;
		kabeL[8][0][0] = 330;
		kabeL[8][0][1] = 570;
		kabeL[8][1][0] = 480;
		kabeL[8][1][1] = 490;
		kabeL[9][0][0] = 560;
		kabeL[9][0][1] = 570;
		kabeL[9][1][0] = 0;
		kabeL[9][1][1] = 230;
		kabeL[10][0][0] = 560;
		kabeL[10][0][1] = 570;
		kabeL[10][1][0] = 250;
		kabeL[10][1][1] = 490;
		kabeL[11][0][0] = 600;
		kabeL[11][0][1] = 610;
		kabeL[11][1][0] = -40;
		kabeL[11][1][1] = 530;
		//アイテムの設定
		//okaneaitemu[][0] = ; okaneaitemu[][1] = ; okaneaitemu[][2] = 300; okaneaitemu[][3] = 1;
		//kaihukuaitemu[][0] = ; kaihukuaitemu[][1] = ; kaihukuaitemu[][2] = ; kaihukuaitemu[][3] = ;
		okaneaitemu[0][0] = 95; okaneaitemu[0][1] = 15; okaneaitemu[0][2] = 300; okaneaitemu[0][3] = 1;
		okaneaitemu[1][0] = 95; okaneaitemu[1][1] = 475; okaneaitemu[1][2] = 300; okaneaitemu[1][3] = 1;
		okaneaitemu[2][0] = 555; okaneaitemu[2][1] = 15; okaneaitemu[2][2] = 300; okaneaitemu[2][3] = 1;
		okaneaitemu[3][0] = 555; okaneaitemu[3][1] = 475; okaneaitemu[3][2] = 300; okaneaitemu[3][3] = 1;
		kaihukuaitemu[0][0] = 195; kaihukuaitemu[0][1] = 115; kaihukuaitemu[0][2] = 100; kaihukuaitemu[0][3] = 1;
		kaihukuaitemu[1][0] = 195; kaihukuaitemu[1][1] = 375; kaihukuaitemu[1][2] = 100; kaihukuaitemu[1][3] = 1;
		kaihukuaitemu[2][0] = 455; kaihukuaitemu[2][1] = 115; kaihukuaitemu[2][2] = 100; kaihukuaitemu[2][3] = 1;
		kaihukuaitemu[3][0] = 455; kaihukuaitemu[3][1] = 375; kaihukuaitemu[3][2] = 100; kaihukuaitemu[3][3] = 1;
		tannikabe[0][0][0] = 305; tannikabe[0][0][1] =335 ; tannikabe[0][1][0] = -30; tannikabe[0][1][1] = 0;
		tannikabe[1][0][0] = 305; tannikabe[1][0][1] = 335; tannikabe[1][1][0] = 495; tannikabe[1][1][1] = 525;
		tannikabe[2][0][0] = 50; tannikabe[2][0][1] = 80; tannikabe[2][1][0] = 225; tannikabe[2][1][1] = 255;
		tannikabe[3][0][0] = 565; tannikabe[3][0][1] = 595; tannikabe[3][1][0] = 225; tannikabe[3][1][1] = 255;
		//敵の設定
		//dekaiteki[][0] = ; dekaiteki[][1] = ; dekaiteki[][5] = ; dekaiteki[][7] = ; dekaiteki[][8] = ;
		dekaiteki[0][0] = 320; dekaiteki[0][1] = 45; dekaiteki[0][5] = 2000; dekaiteki[0][7] = 50; dekaiteki[0][8] = 100;
		dekaiteki[1][0] = 320; dekaiteki[1][1] = 440; dekaiteki[1][5] = 2000; dekaiteki[1][7] = 50; dekaiteki[1][8] = 100;
		dekaiteki[2][0] = 125; dekaiteki[2][1] = 240; dekaiteki[2][5] = 2000; dekaiteki[2][7] = 50; dekaiteki[2][8] = 100;
		dekaiteki[3][0] = 530; dekaiteki[3][1] = 240; dekaiteki[3][5] = 2000; dekaiteki[3][7] = 50; dekaiteki[3][8] = 100;
		//utimakuruteki[][0] = ; utimakuruteki[][1] = ; utimakuruteki[][3] = ; utimakuruteki[][5] = ; utimakuruteki[][10] = ; utimakuruteki[][11] = ; utimakuruteki[][14] = ; utimakuruteki[][15] = ; utimakuruteki[][16] = ; utimakuruteki[][28] = 1000;
		utimakuruteki[0][0] = 95; utimakuruteki[0][1] = -15; utimakuruteki[0][3] = 450; utimakuruteki[0][5] = 800; utimakuruteki[0][10] = 150; utimakuruteki[0][11] = 30; utimakuruteki[0][14] = 5; utimakuruteki[0][15] = 10; utimakuruteki[0][16] = 3; utimakuruteki[0][17] = 1; utimakuruteki[0][28] = 1000;
		utimakuruteki[1][0] = 65; utimakuruteki[1][1] = -15; utimakuruteki[1][3] = 450; utimakuruteki[1][5] = 800; utimakuruteki[1][10] = 150; utimakuruteki[1][11] = 30; utimakuruteki[1][14] = 5; utimakuruteki[1][15] = 10; utimakuruteki[1][16] = 3; utimakuruteki[1][17] = 1; utimakuruteki[1][28] = 1000;
		utimakuruteki[2][0] = 65; utimakuruteki[2][1] = 15; utimakuruteki[2][3] = 450; utimakuruteki[2][5] = 800; utimakuruteki[2][10] = 150; utimakuruteki[2][11] = 30; utimakuruteki[2][14] = 5; utimakuruteki[2][15] = 10; utimakuruteki[2][16] = 3; utimakuruteki[2][17] = 1; utimakuruteki[2][28] = 1000;
		utimakuruteki[3][0] = 65; utimakuruteki[3][1] = 470; utimakuruteki[3][3] = 450; utimakuruteki[3][5] = 800; utimakuruteki[3][10] = 150; utimakuruteki[3][11] = 30; utimakuruteki[3][14] = 5; utimakuruteki[3][15] = 10; utimakuruteki[3][16] = 3; utimakuruteki[3][17] = 1; utimakuruteki[3][28] = 1000;
		utimakuruteki[4][0] = 65; utimakuruteki[4][1] = 500; utimakuruteki[4][3] = 450; utimakuruteki[4][5] = 800; utimakuruteki[4][10] = 150; utimakuruteki[4][11] = 30; utimakuruteki[4][14] = 5; utimakuruteki[4][15] = 10; utimakuruteki[4][16] = 3; utimakuruteki[4][17] = 1; utimakuruteki[4][28] = 1000;
		utimakuruteki[5][0] = 95; utimakuruteki[5][1] = 500; utimakuruteki[5][3] = 450; utimakuruteki[5][5] = 800; utimakuruteki[5][10] = 150; utimakuruteki[5][11] = 30; utimakuruteki[5][14] = 5; utimakuruteki[5][15] = 10; utimakuruteki[5][16] = 3; utimakuruteki[5][17] = 1; utimakuruteki[5][28] = 1000;
		utimakuruteki[6][0] = 555; utimakuruteki[6][1] = 500; utimakuruteki[6][3] = 450; utimakuruteki[6][5] = 800; utimakuruteki[6][10] = 150; utimakuruteki[6][11] = 30; utimakuruteki[6][14] = 5; utimakuruteki[6][15] = 10; utimakuruteki[6][16] = 3; utimakuruteki[6][17] = 1; utimakuruteki[6][28] = 1000;
		utimakuruteki[7][0] = 585; utimakuruteki[7][1] = 500; utimakuruteki[7][3] = 450; utimakuruteki[7][5] = 800; utimakuruteki[7][10] = 150; utimakuruteki[7][11] = 30; utimakuruteki[7][14] = 5; utimakuruteki[7][15] = 10; utimakuruteki[7][16] = 3; utimakuruteki[7][17] = 1; utimakuruteki[7][28] = 1000;
		utimakuruteki[8][0] = 585; utimakuruteki[8][1] = 470; utimakuruteki[8][3] = 450; utimakuruteki[8][5] = 800; utimakuruteki[8][10] = 150; utimakuruteki[8][11] = 30; utimakuruteki[8][14] = 5; utimakuruteki[8][15] = 10; utimakuruteki[8][16] = 3; utimakuruteki[8][17] = 1; utimakuruteki[8][28] = 1000;
		utimakuruteki[9][0] = 585; utimakuruteki[9][1] = 15; utimakuruteki[9][3] = 450; utimakuruteki[9][5] = 800; utimakuruteki[9][10] = 150; utimakuruteki[9][11] = 30; utimakuruteki[9][14] = 5; utimakuruteki[9][15] = 10; utimakuruteki[9][16] = 3; utimakuruteki[9][17] = 1; utimakuruteki[9][28] = 1000;
		utimakuruteki[10][0] = 585; utimakuruteki[10][1] = -15; utimakuruteki[10][3] = 450; utimakuruteki[10][5] = 800; utimakuruteki[10][10] = 150; utimakuruteki[10][11] = 30; utimakuruteki[10][14] = 5; utimakuruteki[10][15] = 10; utimakuruteki[10][16] = 3; utimakuruteki[10][17] = 1; utimakuruteki[10][28] = 1000;
		utimakuruteki[11][0] = 555; utimakuruteki[11][1] = -15; utimakuruteki[11][3] = 450; utimakuruteki[11][5] = 800; utimakuruteki[11][10] = 150; utimakuruteki[11][11] = 30; utimakuruteki[11][14] = 5; utimakuruteki[11][15] = 10; utimakuruteki[11][16] = 3; utimakuruteki[11][17] = 1; utimakuruteki[11][28] = 1000;
		
		
		//アイテムの個数の宣言
		k = 12;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 4;
		kaihukuaitemunokazu = 4;
		memonokazu = 0;
		tanninokazu = 4;
		tannihituyousuu = 4;
		zakotekinokazu = 0;
		ututekinokazu = 0;
		utimakurutekinokazu = 12;
		dekaitekinokazu = 4;

	}
	/*
	if (genzainosutezi == 8) {
		//ここからステージ8の壁の設定

		kabeL[0][0][0] = 240;
		kabeL[0][0][1] = 250;
		kabeL[0][1][0] = 0;
		kabeL[0][1][1] = 490;
		kabeL[1][0][0] = 240;
		kabeL[1][0][1] = 2730;
		kabeL[1][1][0] = 0;
		kabeL[1][1][1] = 10;
		kabeL[2][0][0] = 240;
		kabeL[2][0][1] = 2730;
		kabeL[2][1][0] = 480;
		kabeL[2][1][1] = 490;
		kabeL[3][0][0] = 880;
		kabeL[3][0][1] = 890;
		kabeL[3][1][0] = 0;
		kabeL[3][1][1] = 480;
		kabeL[4][0][0] = 1520;
		kabeL[4][0][1] = 1530;
		kabeL[4][1][0] = 0;
		kabeL[4][1][1] = 480;
		kabeL[5][0][0] = 2160;
		kabeL[5][0][1] = 2170;
		kabeL[5][1][0] = 0;
		kabeL[5][1][1] = 480;
		kabeL[6][0][0] = 2800;
		kabeL[6][0][1] = 2810;
		kabeL[6][1][0] = 0;
		kabeL[6][1][1] = 480;
		kabeL[7][0][0] = 2960;
		kabeL[7][0][1] = 2970;
		kabeL[7][1][0] = 0;
		kabeL[7][1][1] = 480;
		//アイテムの個数の宣言
		k = 8;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 4;
		kaihukuaitemunokazu = 3;
		memonokazu = 0;
		tanninokazu = 1;
		tannihituyousuu = 1;
		zakotekinokazu = 16;
		ututekinokazu = 16;
		utimakurutekinokazu = 16;
		dekaitekinokazu = 16;
	}
	*/

	//0X座標 1Y座標 2ラジアンの値 3スピードを調整するための時間 4実際のスピード 5体力 6体力の色 7体当たりの攻撃力 8倒したとき入手できるお金の金額 9方向転換にかかる時間 10加速度
	//0X座標 1Y座標 2ラジアンの値 3弾を撃つ間隔 4弾が存在するかどうか0で存在しない1で存在する 5体力 6体力の色 7弾のX座標 8弾のY座標  9弾のラジアン 10倒したとき入手できるお金の金額 11体当たりの攻撃力 12動くスピード 13近づき始める距離 14離れ始める距離 15撃つ敵の弾の攻撃力 16撃つ敵の弾のスピード 17撃つ敵の弾の撃つ間隔の時間の実際の時間
	//0X座標 1Y座標 2ラジアンの値 3弾を撃つ間隔 4弾1が存在するかどうか0で存在しない1で存在する 5体力 6体力の色 7弾1のX座標 8弾1のY座標  9弾のラジアン 10倒したとき入手できるお金の金額 11体当たりの攻撃力 12弾2のX座標 13弾2のY座標 14撃つ弾の角度の間隔 15撃つ敵の弾の攻撃力 16撃つ敵の弾のスピード 17撃つ敵の弾の撃つ間隔の時間の実際の時間 18弾3のX 19弾3のY 20弾4のX 21弾4のY 22弾5のX 23弾5のY 24弾2の存在 25弾3の存在 26弾4の存在 27弾5の存在
	//0X座標 1Y座標 2未使用 3未使用 4未使用 5体力 6体力の色 7体当たりの攻撃力 8倒したとき入手できるお金の金額
	if (genzainosutezi == 4) {
		//ここからステージ4の壁の設定

		kabeL[0][0][0] = 150;
		kabeL[0][0][1] = 160;
		kabeL[0][1][0] = 70;
		kabeL[0][1][1] = 410;
		kabeL[1][0][0] = 150;
		kabeL[1][0][1] = 490;
		kabeL[1][1][0] = 70;
		kabeL[1][1][1] = 80;
		kabeL[2][0][0] = 150;
		kabeL[2][0][1] = 490;
		kabeL[2][1][0] = 400;
		kabeL[2][1][1] = 410;
		kabeL[3][0][0] = 480;
		kabeL[3][0][1] = 490;
		kabeL[3][1][0] = 70;
		kabeL[3][1][1] = 410;
		//敵の設定
		for (kurikaesi = 1;  kurikaesi < 15;kurikaesi++) {
			zakoteki[kurikaesi][5] = -10000; zakoteki[kurikaesi][7] = 10; zakoteki[kurikaesi][8] = 300; zakoteki[kurikaesi][9] = 120; zakoteki[kurikaesi][10] = 0.1; zakoteki[kurikaesi][11] = 3000;
		}
		zakoteki[0][5] = 500; zakoteki[0][7] = 10; zakoteki[0][8] = 300; zakoteki[0][9] = 60; zakoteki[0][10] = 0.2; zakoteki[0][11] = 3000;
		zakoteki[0][0] = 160; zakoteki[0][1] = 80; zakoteki[0][3] = 0; zakoteki[0][4] = 0;
		
		//アイテムの個数の宣言
		k = 4;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 0;
		kaihukuaitemunokazu = 0;
		memonokazu = 0;
		tanninokazu = 0;
		tannihituyousuu = 1;
		zakotekinokazu = 15;
		ututekinokazu = 0;
		utimakurutekinokazu = 0;
		dekaitekinokazu = 0;
	}
	/*
	if (genzainosutezi == 10) {
		//ここからステージ5の壁の設定

		kabeL[0][0][0] = 400;
		kabeL[0][0][1] = 410;
		kabeL[0][1][0] = 160;
		kabeL[0][1][1] = 1450;
		kabeL[1][0][0] = -880;
		kabeL[1][0][1] = -870;
		kabeL[1][1][0] = 160;
		kabeL[1][1][1] = 1450;
		kabeL[2][0][0] = -880;
		kabeL[2][0][1] = 410;
		kabeL[2][1][0] = 160;
		kabeL[2][1][1] = 170;
		kabeL[3][0][0] = -880;
		kabeL[3][0][1] = 410;
		kabeL[3][1][0] = 1440;
		kabeL[3][1][1] = 1450;
		kabeL[4][0][0] = -720;
		kabeL[4][0][1] = -710;
		kabeL[4][1][0] = 320;
		kabeL[4][1][1] = 1290;
		kabeL[5][0][0] = -720;
		kabeL[5][0][1] = 80;
		kabeL[5][1][0] = 320;
		kabeL[5][1][1] = 330;
		kabeL[6][0][0] = -720;
		kabeL[6][0][1] = 250;
		kabeL[6][1][0] = 1280;
		kabeL[6][1][1] = 1290;
		kabeL[7][0][0] = -560;
		kabeL[7][0][1] = -550;
		kabeL[7][1][0] = 480;
		kabeL[7][1][1] = 1130;
		kabeL[8][0][0] = -560;
		kabeL[8][0][1] = 250;
		kabeL[8][1][0] = 480;
		kabeL[8][1][1] = 490;
		kabeL[9][0][0] = -560;
		kabeL[9][0][1] = 90;
		kabeL[9][1][0] = 1120;
		kabeL[9][1][1] = 1130;
		kabeL[10][0][0] = -400;
		kabeL[10][0][1] = -390;
		kabeL[10][1][0] = 640;
		kabeL[10][1][1] = 970;
		kabeL[11][0][0] = -400;
		kabeL[11][0][1] = -240;
		kabeL[11][1][0] = 640;
		kabeL[11][1][1] = 650;
		kabeL[12][0][0] = -400;
		kabeL[12][0][1] = -70;
		kabeL[12][1][0] = 960;
		kabeL[12][1][1] = 970;
		kabeL[13][0][0] = -240;
		kabeL[13][0][1] = -70;
		kabeL[13][1][0] = 800;
		kabeL[13][1][1] = 810;
		kabeL[14][0][0] = -80;
		kabeL[14][0][1] = -70;
		kabeL[14][1][0] = 480;
		kabeL[14][1][1] = 970;
		kabeL[15][0][0] = 80;
		kabeL[15][0][1] = 90;
		kabeL[15][1][0] = 640;
		kabeL[15][1][1] = 1130;
		kabeL[16][0][0] = 240;
		kabeL[16][0][1] = 250;
		kabeL[16][1][0] = 160;
		kabeL[16][1][1] = 1290;
		//敵の設定
		//どうにかして楽に変数に値を入れたい。けど無理っぽい
		//double	utimakuruteki[18][28] = {//0X座標 1Y座標 2ラジアンの値 3弾を撃つ間隔 4弾1が存在するかどうか0で存在しない1で存在する 5体力 6体力の色 7弾1のX座標 8弾1のY座標  9弾のラジアン 10倒したとき入手できるお金の金額 11体当たりの攻撃力 12弾2のX座標 13弾2のY座標 14撃つ弾の角度の間隔 15撃つ敵の弾の攻撃力 16撃つ敵の弾のスピード 17撃つ敵の弾の撃つ間隔の時間の実際の時間 18弾3のX 19弾3のY 20弾4のX 21弾4のY 22弾5のX 23弾5のY 24弾2の存在 25弾3の存在 26弾4の存在 27弾5の存在


		//アイテムの個数の宣言
		k = 17;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 0;
		kaihukuaitemunokazu = 2;
		memonokazu = 0;
		tanninokazu = 1;
		tannihituyousuu = 1;
		zakotekinokazu = 0;
		ututekinokazu = 0;
		utimakurutekinokazu = 18;
		dekaitekinokazu = 0;


	}
	*/

	if (genzainosutezi == 8) {
		k = 26;//壁の個数k個ある。
		n = 0;//ダメージ壁の個数n個ある。
		kuroikabenokazu = 0;
		okaneaitemunokazu = 1;
		kaihukuaitemunokazu = 9;
		memonokazu = 6;
		tanninokazu = 10;
		tannihituyousuu = 10;
		zakotekinokazu = 30;
		ututekinokazu = 84;
		utimakurutekinokazu = 32;
		dekaitekinokazu = 8;
		damezikabenokougekiryoku = 100;
		//ここからステージ8の緑の壁の設定。
		kabeL[0][0][0] = -30;
		kabeL[0][0][1] = 0;
		kabeL[0][1][0] = -30;
		kabeL[0][1][1] = 480;
		kabeL[1][0][0] = -30;
		kabeL[1][0][1] = 1230;
		kabeL[1][1][0] = -30;
		kabeL[1][1][1] = 0;
		kabeL[2][0][0] = -30;
		kabeL[2][0][1] = 1230;
		kabeL[2][1][0] = 480;
		kabeL[2][1][1] = 510;
		kabeL[3][0][0] = 1200;
		kabeL[3][0][1] = 1230;
		kabeL[3][1][0] = -30;
		kabeL[3][1][1] = 180;
		kabeL[4][0][0] = 1200;
		kabeL[4][0][1] = 1230;
		kabeL[4][1][0] = 300;
		kabeL[4][1][1] = 510;
		kabeL[5][0][0] = 1200;
		kabeL[5][0][1] = 1800;
		kabeL[5][1][0] = 150;
		kabeL[5][1][1] = 180;
		kabeL[6][0][0] = 1200;
		kabeL[6][0][1] = 1800;
		kabeL[6][1][0] = 300;
		kabeL[6][1][1] = 330;
		kabeL[7][0][0] = 1770;
		kabeL[7][0][1] = 1800;
		kabeL[7][1][0] = -30;
		kabeL[7][1][1] = 180;
		kabeL[8][0][0] = 1770;
		kabeL[8][0][1] = 1800;
		kabeL[8][1][0] = 300;
		kabeL[8][1][1] = 510;
		kabeL[9][0][0] = 1770;
		kabeL[9][0][1] = 1800;
		kabeL[9][1][0] = 690;
		kabeL[9][1][1] = 1230;
		kabeL[10][0][0] = 1770;
		kabeL[10][0][1] = 2430;
		kabeL[10][1][0] = -30;
		kabeL[10][1][1] = 0;
		kabeL[11][0][0] = 1770;
		kabeL[11][0][1] = 2040;
		kabeL[11][1][0] = 480;
		kabeL[11][1][1] = 510;
		kabeL[12][0][0] = 1770;
		kabeL[12][0][1] = 2040;
		kabeL[12][1][0] = 690;
		kabeL[12][1][1] = 720;
		kabeL[13][0][0] = 1770;
		kabeL[13][0][1] = 2430;
		kabeL[13][1][0] = 1200;
		kabeL[13][1][1] = 1230;
		kabeL[14][0][0] = 2010;
		kabeL[14][0][1] = 2040;
		kabeL[14][1][0] = 480;
		kabeL[14][1][1] = 720;
		kabeL[15][0][0] = 2160;
		kabeL[15][0][1] = 2190;
		kabeL[15][1][0] = 480;
		kabeL[15][1][1] = 720;
		kabeL[16][0][0] = 2160;
		kabeL[16][0][1] = 2430;
		kabeL[16][1][0] = 480;
		kabeL[16][1][1] = 510;
		kabeL[17][0][0] = 2160;
		kabeL[17][0][1] = 2430;
		kabeL[17][1][0] = 690;
		kabeL[17][1][1] = 720;
		kabeL[18][0][0] = 2400;
		kabeL[18][0][1] = 2430;
		kabeL[18][1][0] = -30;
		kabeL[18][1][1] = 510;
		kabeL[19][0][0] = 2400;
		kabeL[19][0][1] = 2430;
		kabeL[19][1][0] = 690;
		kabeL[19][1][1] = 1230;//左、右、上、下の順番。

		memo[0][0] = 265; memo[0][1] = 180;
		memo[1][0] = 800; memo[1][1] = 240;
		memo[2][0] = 1300; memo[2][1] = 40;
		memo[3][0] = 2000; memo[3][1] = 240;
		memo[4][0] = 2040; memo[4][1] = 540;
		memo[5][0] = 1900; memo[5][1] = 900;

		

		kabeL[20][0][0] = 1440;
		kabeL[20][0][1] = 1470;
		kabeL[20][1][0] = 210;
		kabeL[20][1][1] = 300;
		kabeL[21][0][0] = 1500;
		kabeL[21][0][1] = 1530;
		kabeL[21][1][0] = 180;
		kabeL[21][1][1] = 270;
		kabeL[22][0][0] = 1560;
		kabeL[22][0][1] = 1590;
		kabeL[22][1][0] = 210;
		kabeL[22][1][1] = 300;
		kabeL[23][0][0] = 1620;
		kabeL[23][0][1] = 1650;
		kabeL[23][1][0] = 180;
		kabeL[23][1][1] = 270;
		kabeL[24][0][0] = 1680;
		kabeL[24][0][1] = 1710;
		kabeL[24][1][0] = 210;
		kabeL[24][1][1] = 300;
		kabeL[25][0][0] = 1740;
		kabeL[25][0][1] = 1770;
		kabeL[25][1][0] = 180;
		kabeL[25][1][1] = 270;
		tannikabe[0][0][0] = 2085; tannikabe[0][0][1] = 2115; tannikabe[0][1][0] = 940; tannikabe[0][1][1] = 970;
		tannikabe[1][0][0] = 2285; tannikabe[1][0][1] = 2315; tannikabe[1][1][0] = 1140; tannikabe[1][1][1] = 1170;
		tannikabe[2][0][0] = 1885; tannikabe[2][0][1] = 1915; tannikabe[2][1][0] = 1140; tannikabe[2][1][1] = 1170;
		tannikabe[3][0][0] = 2285; tannikabe[3][0][1] = 2315; tannikabe[3][1][0] = 740; tannikabe[3][1][1] = 770;
		tannikabe[4][0][0] = 1885; tannikabe[4][0][1] = 1915; tannikabe[4][1][0] = 740; tannikabe[4][1][1] = 770;
		tannikabe[5][0][0] = 2085; tannikabe[5][0][1] = 2115; tannikabe[5][1][0] = 225; tannikabe[5][1][1] = 255;
		tannikabe[6][0][0] = 2285; tannikabe[6][0][1] = 2315; tannikabe[6][1][0] = 425; tannikabe[6][1][1] = 455;
		tannikabe[7][0][0] = 1885; tannikabe[7][0][1] = 1915; tannikabe[7][1][0] = 425; tannikabe[7][1][1] = 455;
		tannikabe[8][0][0] = 2285; tannikabe[8][0][1] = 2315; tannikabe[8][1][0] = 25; tannikabe[8][1][1] = 55;
		tannikabe[9][0][0] = 1885; tannikabe[9][0][1] = 1915; tannikabe[9][1][0] = 25; tannikabe[9][1][1] = 55;

		dekaiteki[0][0] = 1900; dekaiteki[0][1] = 755; dekaiteki[0][5] = 1300; dekaiteki[0][7] = 300; dekaiteki[0][8] = 1000;
		dekaiteki[1][0] = 2300; dekaiteki[1][1] = 755; dekaiteki[1][5] = 1300; dekaiteki[1][7] = 300; dekaiteki[1][8] = 1000;
		dekaiteki[2][0] = 1900; dekaiteki[2][1] = 1155; dekaiteki[2][5] = 1300; dekaiteki[2][7] = 300; dekaiteki[2][8] = 1000;
		dekaiteki[3][0] = 2300; dekaiteki[3][1] = 1155; dekaiteki[3][5] = 1300; dekaiteki[3][7] = 300; dekaiteki[3][8] = 1000;
		dekaiteki[4][0] = 1900; dekaiteki[4][1] = 40; dekaiteki[4][5] = 1300; dekaiteki[4][7] = 300; dekaiteki[4][8] = 1000;
		dekaiteki[5][0] = 2300; dekaiteki[5][1] = 40; dekaiteki[5][5] = 1300; dekaiteki[5][7] = 300; dekaiteki[5][8] = 1000;
		dekaiteki[6][0] = 1900; dekaiteki[6][1] = 440; dekaiteki[6][5] = 1300; dekaiteki[6][7] = 300; dekaiteki[6][8] = 1000;
		dekaiteki[7][0] = 2300; dekaiteki[7][1] = 440; dekaiteki[7][5] = 1300; dekaiteki[7][7] = 300; dekaiteki[7][8] = 1000;

		for ( i = 0; i < 4; i++)
		{
			for ( kurikaesi = 0; kurikaesi < 4; kurikaesi++)
			{
				utimakuruteki[i * 4 + kurikaesi][0] = 2055+kurikaesi*30; utimakuruteki[i * 4 + kurikaesi][1] = 195 + i * 30; utimakuruteki[i * 4 + kurikaesi][3] = 180; utimakuruteki[i * 4 + kurikaesi][5] = 300; utimakuruteki[i * 4 + kurikaesi][10] = 500; utimakuruteki[i * 4 + kurikaesi][11] = 300; utimakuruteki[i * 4 + kurikaesi][14] = 25; utimakuruteki[i * 4 + kurikaesi][15] = 50; utimakuruteki[i * 4 + kurikaesi][16] = 3; utimakuruteki[i * 4 + kurikaesi][17] = 1; utimakuruteki[i * 4 + kurikaesi][28] = 0;
			}
		}
		for (i = 0; i < 4; i++)
		{
			for (kurikaesi = 0; kurikaesi < 4; kurikaesi++)
			{
				utimakuruteki[i * 4 + kurikaesi+16][0] = 2055 + kurikaesi * 30; utimakuruteki[i * 4 + kurikaesi+16][1] = 910 + i * 30; utimakuruteki[i * 4 + kurikaesi+16][3] = 180; utimakuruteki[i * 4 + kurikaesi+16][5] = 300; utimakuruteki[i * 4 + kurikaesi+16][10] = 500; utimakuruteki[i * 4 + kurikaesi+16][11] = 300; utimakuruteki[i * 4 + kurikaesi+16][14] = 25; utimakuruteki[i * 4 + kurikaesi+16][15] = 50; utimakuruteki[i * 4 + kurikaesi+16][16] = 3; utimakuruteki[i * 4 + kurikaesi+16][17] = 1; utimakuruteki[i * 4 + kurikaesi+16][28] = 0;
			}
		}

		for (kurikaesi = 0; kurikaesi < 30; kurikaesi++) {
			zakoteki[kurikaesi][0] = 200 - kurikaesi * 30; zakoteki[kurikaesi][1] = 240; zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0;
			zakoteki[kurikaesi][5] = 1000; zakoteki[kurikaesi][7] = 50; zakoteki[kurikaesi][8] = 300; zakoteki[kurikaesi][9] = 180; zakoteki[kurikaesi][10] = 0.03; zakoteki[kurikaesi][11] = 6000;
		}

		for (kurikaesi = 0; kurikaesi <= 20; kurikaesi++) {
			ututeki[kurikaesi][0] = kurikaesi * 30; ututeki[kurikaesi][1] = 30; ututeki[kurikaesi][3] = 210; ututeki[kurikaesi][5] = 500; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 2; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 30; ututeki[kurikaesi][16] = 5; ututeki[kurikaesi][17] = kurikaesi*10; ututeki[kurikaesi][18] = 3000;
		}
		for (kurikaesi = 21; kurikaesi <= 41; kurikaesi++) {
			ututeki[kurikaesi][0] = (kurikaesi-20) * 30; ututeki[kurikaesi][1] = 60; ututeki[kurikaesi][3] = 210; ututeki[kurikaesi][5] = 500; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 2; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 30; ututeki[kurikaesi][16] = 5; ututeki[kurikaesi][17] = (kurikaesi-21)*10; ututeki[kurikaesi][18] = 3000;
		}
		for (kurikaesi = 42; kurikaesi <= 62; kurikaesi++) {
			ututeki[kurikaesi][0] = (kurikaesi - 42) * 30; ututeki[kurikaesi][1] = 420; ututeki[kurikaesi][3] = 210; ututeki[kurikaesi][5] = 500; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 2; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 30; ututeki[kurikaesi][16] = 5; ututeki[kurikaesi][17] = (kurikaesi - 42) * 10; ututeki[kurikaesi][18] = 3000;
		}
		for (kurikaesi = 63; kurikaesi <= 83; kurikaesi++) {
			ututeki[kurikaesi][0] = (kurikaesi - 63) * 30; ututeki[kurikaesi][1] = 450; ututeki[kurikaesi][3] = 210; ututeki[kurikaesi][5] = 500; ututeki[kurikaesi][10] = 40; ututeki[kurikaesi][11] = 30; ututeki[kurikaesi][12] = 2; ututeki[kurikaesi][13] = 0; ututeki[kurikaesi][14] = 0; ututeki[kurikaesi][15] = 30; ututeki[kurikaesi][16] = 5; ututeki[kurikaesi][17] = (kurikaesi - 63) * 10; ututeki[kurikaesi][18] = 3000;
		}
		
		//utimakuruteki[0][0] = 2100; utimakuruteki[0][1] = 330; utimakuruteki[0][3] = 240; utimakuruteki[0][5] = 500; utimakuruteki[0][10] = 100; utimakuruteki[0][11] = 30; utimakuruteki[0][14] = 15; utimakuruteki[0][15] = 20; utimakuruteki[0][16] = 1; utimakuruteki[0][17] = 1; utimakuruteki[0][28] = 1000;

		okaneaitemu[0][0] = 2100; okaneaitemu[0][1] = 700; okaneaitemu[0][2] = 3000; okaneaitemu[0][3] = 1;
		for ( i = 0; i < 3; i++)
		{
			for ( kurikaesi = 0; kurikaesi < 3; kurikaesi++)
			{
				kaihukuaitemu[i*3+kurikaesi][0] = 2070+kurikaesi*30; kaihukuaitemu[i*3+kurikaesi][1] = 600+i*30; kaihukuaitemu[i*3+kurikaesi][2] = 600; kaihukuaitemu[i*3+kurikaesi][3] = 1;
			}
		}		
	}
	/*if (genzainosutezi == 8) {
		//ここからステージ8の壁の設定

		kabeL[0][0][0] = ;
		kabeL[0][0][1] = ;
		kabeL[0][1][0] = ;
		kabeL[0][1][1] = ;
		kabeL[1][0][0] = ;
		kabeL[1][0][1] = ;
		kabeL[1][1][0] = ;
		kabeL[1][1][1] = ;
		kabeL[2][0][0] = ;
		kabeL[2][0][1] = ;
		kabeL[2][1][0] = ;
		kabeL[2][1][1] = ;
		kabeL[3][0][0] = ;
		kabeL[3][0][1] = ;
		kabeL[3][1][0] = ;
		kabeL[3][1][1] = ;
		kabeL[4][0][0] = ;
		kabeL[4][0][1] = ;
		kabeL[4][1][0] = ;
		kabeL[4][1][1] = ;
		kabeL[5][0][0] = ;
		kabeL[5][0][1] = ;
		kabeL[5][1][0] = ;
		kabeL[5][1][1] = ;
		kabeL[6][0][0] = ;
		kabeL[6][0][1] = ;
		kabeL[6][1][0] = ;
		kabeL[6][1][1] = ;
		kabeL[7][0][0] = ;
		kabeL[7][0][1] = ;
		kabeL[7][1][0] = ;
		kabeL[7][1][1] = ;
		kabeL[8][0][0] = ;
		kabeL[8][0][1] = ;
		kabeL[8][1][0] = ;
		kabeL[8][1][1] = ;
		kabeL[9][0][0] = ;
		kabeL[9][0][1] = ;
		kabeL[9][1][0] = ;
		kabeL[9][1][1] = ;
	}*/
	tairyoku = tairyokusaidaiti;
	tairyokuzenkai = tairyokusaidaiti;
	mausuhidari = 0;
	mausuhidarizenkai = 0;
	mausuhidariutu = 0;
	genzainotanninokazu = 0;
	for (kurikaesi = 0; kurikaesi++; kurikaesi < 26) {
		tametama[kurikaesi][6] = 0;
	}
	for (kurikaesi = 0; kurikaesi++; kurikaesi < 50) {
		tama[kurikaesi][6] = 0;
	}
	for (kurikaesi = 0; kurikaesi++; kurikaesi < 18) {
		utimakuruteki[kurikaesi][4] = 0; utimakuruteki[kurikaesi][24] = 0; utimakuruteki[kurikaesi][25] = 0; utimakuruteki[kurikaesi][26] = 0; utimakuruteki[kurikaesi][27] = 0;
	}
	for (kurikaesi = 0; kurikaesi++; kurikaesi < 16) {
		ututeki[kurikaesi][4] = 0;
	}//それぞれ敵の最大数まで繰り返すようにしなければいけない。完成前にもう一度設定しなおさないといけない。
	sutezinogimikku = 0;
	genzainozikan = 0;
	StopSoundMem(ongakumenyu);//メニュー画面の音楽を止める。
	PlaySoundMem(ongakusentou, DX_PLAYTYPE_LOOP);//戦闘画面の音楽再生。

	for (kurikaesi = 0; kurikaesi < 50; kurikaesi++) {
		tama[kurikaesi][6] = 0;
	}
	for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
		tametama[kurikaesi][6] = 0;
	}
	for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
		ututeki[kurikaesi][4] = 0;
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu;kurikaesi++) {
		utimakuruteki[kurikaesi][4] = 0; utimakuruteki[kurikaesi][24] = 0; utimakuruteki[kurikaesi][25] = 0; utimakuruteki[kurikaesi][26] = 0; utimakuruteki[kurikaesi][27] = 0;
	}//とりあえず敵の数だけ弾を消すようにしてみた。要注意。

	
	
	 //ゲームスタートする前にクリックするまで停止するプログラム
	muteki = 30;
	mausuhidari = 2;
	while (mausuhidari != 1&&genzainosutezi!=0) {
		
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 )

		{
			mausuhidari++;
			// 押されている
		}
		if (mausuhidarizenkai == mausuhidari) { mausuhidari = 0; mausuhidarizenkai = 0; }
		mausuhidarizenkai = mausuhidari;
		
		if (CheckHitKey(KEY_INPUT_NUMPADENTER) == 1) { genzainosutezi = 0; break;  }
	SetBackgroundColor(200, 200, 200);
	//描画ゾーン
	ClearDrawScreen();
	//DrawGraph(0, 0, haikei, false);

	for (m = 0; m < n; m++)
	{
		DrawExtendGraph(kabeD[m][0][0], kabeD[m][1][0], (kabeD[m][0][1] - 1), (kabeD[m][1][1] - 1), bannou2, false);
	}
	for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++)
	{
		DrawExtendGraph(kuroikabe[kurikaesi][0][0], kuroikabe[kurikaesi][1][0], (kuroikabe[kurikaesi][0][1] - 1), (kuroikabe[kurikaesi][1][1] - 1), kuroigazou, false);
	}
	for (i = 0; i < k; i++)
	{
		DrawExtendGraph(kabeL[i][0][0], kabeL[i][1][0], (kabeL[i][0][1] - 1), (kabeL[i][1][1] - 1), bannou, false);
	}
	for (p = 0; p < tanninokazu; p++)
	{
		DrawExtendGraph(tannikabe[p][0][0], tannikabe[p][1][0], (tannikabe[p][0][1] - 1), (tannikabe[p][1][1] - 1), tannigazou, false);
	}
	if (tairyoku > 0) {
		if ((muteki >= 5 && muteki < 10) || (muteki >= 15 && muteki < 20) ||
			(muteki >= 25 && muteki < 30)/* || (muteki >= 35 && muteki < 40) ||
										 (muteki >= 45 && muteki < 50) || (muteki >= 55 && muteki < 60) ||
										 (muteki >= 65 && muteki < 70) || (muteki >= 75 && muteki < 80) ||
										 (muteki >= 85 && muteki < 90) || (muteki >= 95 && muteki < 100)*/) {
			DrawExtendGraph(315, 235, 324, 244, touhunaku, false);
		}
		else if (muteki >= 0 && muteki < 30) {}
		else if (mausuhidari >= 100) { DrawExtendGraph(315, 235, 324, 244, touhusuppai, false); }
		else if (mausuhidari >= 50) { DrawExtendGraph(315, 235, 324, 244, touhuhunbari, false); }
		else if (mausuhidari >= 1) { DrawExtendGraph(315, 235, 324, 244, touhumagao, false); }
		else if (mausuhidari == 0) { DrawExtendGraph(315, 235, 324, 244, touhu, false); }
	}

	for (i = 0; i < k; i++) {
		DrawFormatString(kabeL[i][0][0], kabeL[i][1][0], GetColor(255, 0, 0), "(%d)", i);
	}
	for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
		if (tama[kurikaesi][6] == 1) {
			DrawGraph(tama[kurikaesi][0] - 2, tama[kurikaesi][1] - 2, tamagazou, true);
		}
	}
	for (kurikaesi = 0; kurikaesi < 32; kurikaesi++) {
		if (tametama[kurikaesi][6] == 1) {
			DrawGraph(tametama[kurikaesi][0] - 2, tametama[kurikaesi][1] - 2, tamagazou, true);
		}
	}

	//DrawGraph(30, 30, huriwakeyarinaosi, true);
	//DrawGraph(30, 30, bosuteki, true);
	//回復アイテムの描写。
	for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
		if (kaihukuaitemu[kurikaesi][3] == 1) {
			DrawGraph(kaihukuaitemu[kurikaesi][0] - 5, kaihukuaitemu[kurikaesi][1] - 5, kaihukuaitemugazou, false);
		}
	}
	//お金アイテムの描写。
	for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
		if (okaneaitemu[kurikaesi][3] == 1) {
			DrawGraph(okaneaitemu[kurikaesi][0] - 5, okaneaitemu[kurikaesi][1] - 5, okaneaitemugazou, false);
		}
	}
	//ザコ敵の描写
	for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
		if (zakoteki[kurikaesi][5] >= 1) {
			if (zakoteki[kurikaesi][5] <= 256 && zakoteki[kurikaesi][5] >= 1)
			{
				zakoteki[kurikaesi][6] = GetColor(zakoteki[kurikaesi][5] - 1, 0, 0); //黒から赤
			}
			else if (zakoteki[kurikaesi][5] <= 512 && zakoteki[kurikaesi][5] >= 257)
			{
				zakoteki[kurikaesi][6] = GetColor(255, zakoteki[kurikaesi][5] - 257, 0);//赤から黄
			}
			else if (zakoteki[kurikaesi][5] <= 768 && zakoteki[kurikaesi][5] >= 513)
			{
				zakoteki[kurikaesi][6] = GetColor(768 - zakoteki[kurikaesi][5], 255, 0);//黄から緑
			}
			else if (zakoteki[kurikaesi][5] <= 1024 && zakoteki[kurikaesi][5] >= 769)
			{
				zakoteki[kurikaesi][6] = GetColor(0, 255, zakoteki[kurikaesi][5] - 769);//緑から水
			}
			else if (zakoteki[kurikaesi][5] <= 1280 && zakoteki[kurikaesi][5] >= 1025)
			{
				zakoteki[kurikaesi][6] = GetColor(0, 1280 - zakoteki[kurikaesi][5], 255);//水から青
			}
			else if (zakoteki[kurikaesi][5] <= 1536 && zakoteki[kurikaesi][5] >= 1281)
			{
				zakoteki[kurikaesi][6] = GetColor(zakoteki[kurikaesi][5] - 1281, 0, 255);//青から紫
			}
			else if (zakoteki[kurikaesi][5] <= 1792 && zakoteki[kurikaesi][5] >= 1537)
			{
				zakoteki[kurikaesi][6] = GetColor(255, zakoteki[kurikaesi][5] - 1537, 255);//紫から白
			}
			else if (zakoteki[kurikaesi][5] >= 1793)
			{
				zakoteki[kurikaesi][6] = GetColor(255, 255, 255);//白
			}
			DrawCircle(zakoteki[kurikaesi][0], zakoteki[kurikaesi][1], 3, zakoteki[kurikaesi][6], TRUE);//円を描く。
			DrawGraph(zakoteki[kurikaesi][0] - 300, zakoteki[kurikaesi][1] - 300, zakotekinogazou, true);
			//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
			//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
		}
	}
	//撃つ敵の描写
	for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
		if (ututeki[kurikaesi][5] >= 1) {
			if (ututeki[kurikaesi][5] <= 256 && ututeki[kurikaesi][5] >= 1)
			{
				ututeki[kurikaesi][6] = GetColor(ututeki[kurikaesi][5] - 1, 0, 0); //黒から赤
			}
			else if (ututeki[kurikaesi][5] <= 512 && ututeki[kurikaesi][5] >= 257)
			{
				ututeki[kurikaesi][6] = GetColor(255, ututeki[kurikaesi][5] - 257, 0);//赤から黄
			}
			else if (ututeki[kurikaesi][5] <= 768 && ututeki[kurikaesi][5] >= 513)
			{
				ututeki[kurikaesi][6] = GetColor(768 - ututeki[kurikaesi][5], 255, 0);//黄から緑
			}
			else if (ututeki[kurikaesi][5] <= 1024 && ututeki[kurikaesi][5] >= 769)
			{
				ututeki[kurikaesi][6] = GetColor(0, 255, ututeki[kurikaesi][5] - 769);//緑から水
			}
			else if (ututeki[kurikaesi][5] <= 1280 && ututeki[kurikaesi][5] >= 1025)
			{
				ututeki[kurikaesi][6] = GetColor(0, 1280 - ututeki[kurikaesi][5], 255);//水から青
			}
			else if (ututeki[kurikaesi][5] <= 1536 && ututeki[kurikaesi][5] >= 1281)
			{
				ututeki[kurikaesi][6] = GetColor(ututeki[kurikaesi][5] - 1281, 0, 255);//青から紫
			}
			else if (ututeki[kurikaesi][5] <= 1792 && ututeki[kurikaesi][5] >= 1537)
			{
				ututeki[kurikaesi][6] = GetColor(255, ututeki[kurikaesi][5] - 1537, 255);//紫から白
			}
			else if (ututeki[kurikaesi][5] >= 1793)
			{
				ututeki[kurikaesi][6] = GetColor(255, 255, 255);//白
			}
			DrawCircle(ututeki[kurikaesi][0], ututeki[kurikaesi][1], 3, ututeki[kurikaesi][6], TRUE);//円を描く。
			DrawGraph(ututeki[kurikaesi][0] - 300, ututeki[kurikaesi][1] - 300, ututekinogazou, true);
			//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
			//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
		}
	}
	for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
		if (ututeki[kurikaesi][4] == 1) {
			DrawGraph(ututeki[kurikaesi][7] - 2, ututeki[kurikaesi][8] - 2, ututekinotamanogazou, true);
		}
	}
	//撃ちまくる敵の描写
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][5] >= 1) {
			if (utimakuruteki[kurikaesi][5] <= 256 && utimakuruteki[kurikaesi][5] >= 1)
			{
				utimakuruteki[kurikaesi][6] = GetColor(utimakuruteki[kurikaesi][5] - 1, 0, 0); //黒から赤
			}
			else if (utimakuruteki[kurikaesi][5] <= 512 && utimakuruteki[kurikaesi][5] >= 257)
			{
				utimakuruteki[kurikaesi][6] = GetColor(255, utimakuruteki[kurikaesi][5] - 257, 0);//赤から黄
			}
			else if (utimakuruteki[kurikaesi][5] <= 768 && utimakuruteki[kurikaesi][5] >= 513)
			{
				utimakuruteki[kurikaesi][6] = GetColor(768 - utimakuruteki[kurikaesi][5], 255, 0);//黄から緑
			}
			else if (utimakuruteki[kurikaesi][5] <= 1024 && utimakuruteki[kurikaesi][5] >= 769)
			{
				utimakuruteki[kurikaesi][6] = GetColor(0, 255, utimakuruteki[kurikaesi][5] - 769);//緑から水
			}
			else if (utimakuruteki[kurikaesi][5] <= 1280 && utimakuruteki[kurikaesi][5] >= 1025)
			{
				utimakuruteki[kurikaesi][6] = GetColor(0, 1280 - utimakuruteki[kurikaesi][5], 255);//水から青
			}
			else if (utimakuruteki[kurikaesi][5] <= 1536 && utimakuruteki[kurikaesi][5] >= 1281)
			{
				utimakuruteki[kurikaesi][6] = GetColor(utimakuruteki[kurikaesi][5] - 1281, 0, 255);//青から紫
			}
			else if (utimakuruteki[kurikaesi][5] <= 1792 && utimakuruteki[kurikaesi][5] >= 1537)
			{
				utimakuruteki[kurikaesi][6] = GetColor(255, utimakuruteki[kurikaesi][5] - 1537, 255);//紫から白
			}
			else if (utimakuruteki[kurikaesi][5] >= 1793)
			{
				utimakuruteki[kurikaesi][6] = GetColor(255, 255, 255);//白
			}
			DrawCircle(utimakuruteki[kurikaesi][0], utimakuruteki[kurikaesi][1], 3, utimakuruteki[kurikaesi][6], TRUE);//円を描く。
			DrawGraph(utimakuruteki[kurikaesi][0] - 300, utimakuruteki[kurikaesi][1] - 300, utimakurutekinogazou, true);
			//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
			//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！(←使わなくなった。)
		}
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][4] == 1) {
			DrawGraph(utimakuruteki[kurikaesi][7] - 2, utimakuruteki[kurikaesi][8] - 2, aoigazou, true);
		}
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][24] == 1) {
			DrawGraph(utimakuruteki[kurikaesi][12] - 2, utimakuruteki[kurikaesi][13] - 2, aoigazou, true);
		}
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][25] == 1) {
			DrawGraph(utimakuruteki[kurikaesi][18] - 2, utimakuruteki[kurikaesi][19] - 2, aoigazou, true);
		}
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][26] == 1) {
			DrawGraph(utimakuruteki[kurikaesi][20] - 2, utimakuruteki[kurikaesi][21] - 2, aoigazou, true);
		}
	}
	for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
		if (utimakuruteki[kurikaesi][27] == 1) {
			DrawGraph(utimakuruteki[kurikaesi][22] - 2, utimakuruteki[kurikaesi][23] - 2, aoigazou, true);
		}
	}
	//デカい敵の描写
	for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
		if (dekaiteki[kurikaesi][5] >= 1) {
			if (dekaiteki[kurikaesi][5] <= 256 && dekaiteki[kurikaesi][5] >= 1)
			{
				dekaiteki[kurikaesi][6] = GetColor(dekaiteki[kurikaesi][5] - 1, 0, 0); //黒から赤
			}
			else if (dekaiteki[kurikaesi][5] <= 512 && dekaiteki[kurikaesi][5] >= 257)
			{
				dekaiteki[kurikaesi][6] = GetColor(255, dekaiteki[kurikaesi][5] - 257, 0);//赤から黄
			}
			else if (dekaiteki[kurikaesi][5] <= 768 && dekaiteki[kurikaesi][5] >= 513)
			{
				dekaiteki[kurikaesi][6] = GetColor(768 - dekaiteki[kurikaesi][5], 255, 0);//黄から緑
			}
			else if (dekaiteki[kurikaesi][5] <= 1024 && dekaiteki[kurikaesi][5] >= 769)
			{
				dekaiteki[kurikaesi][6] = GetColor(0, 255, dekaiteki[kurikaesi][5] - 769);//緑から水
			}
			else if (dekaiteki[kurikaesi][5] <= 1280 && dekaiteki[kurikaesi][5] >= 1025)
			{
				dekaiteki[kurikaesi][6] = GetColor(0, 1280 - dekaiteki[kurikaesi][5], 255);//水から青
			}
			else if (dekaiteki[kurikaesi][5] <= 1536 && dekaiteki[kurikaesi][5] >= 1281)
			{
				dekaiteki[kurikaesi][6] = GetColor(dekaiteki[kurikaesi][5] - 1281, 0, 255);//青から紫
			}
			else if (dekaiteki[kurikaesi][5] <= 1792 && dekaiteki[kurikaesi][5] >= 1537)
			{
				dekaiteki[kurikaesi][6] = GetColor(255, dekaiteki[kurikaesi][5] - 1537, 255);//紫から白
			}
			else if (dekaiteki[kurikaesi][5] >= 1793)
			{
				dekaiteki[kurikaesi][6] = GetColor(255, 255, 255);//白
			}
			DrawCircle(dekaiteki[kurikaesi][0], dekaiteki[kurikaesi][1], 3, dekaiteki[kurikaesi][6], TRUE);//円を描く。
			DrawGraph(dekaiteki[kurikaesi][0] - 300, dekaiteki[kurikaesi][1] - 300, dekaitekinogazou, true);
			//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
			//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
		}
	}
	//ステージ上のメモの設定
	if (genzainosutezi == 1) {
		DrawFormatString(memo[0][0], memo[0][1], GetColor(0, 0, 0), "<<移動ボタン>>\n     W\n     ↑\n  A←  →D     右へ進む  →  →  →  →  →  →\n     ↓\n     S");
		DrawFormatString(memo[1][0], memo[1][1], GetColor(0, 0, 0), "マウスカーソルで敵を狙う     右へ進む  →  →  →  →  →  →\n左クリック長押しで溜める\n右下の黄色いゲージが溜まったら離す\n溜めは2段階ある\n溜めない方がダメージ効率がよい");
		DrawFormatString(memo[2][0], memo[2][1], GetColor(0, 0, 0), "緑色の壁は通り抜けられない\n紫の壁は触れるとダメージを受ける\n黒い壁に触れると即死\nENTERを押すとメニュー画面に戻る\n(誤って押さないように注意)");
		DrawFormatString(memo[3][0], memo[3][1], GetColor(0, 0, 0), "敵に弾を当てて倒そう\n敵を倒すと$が手に入る\n敵の本体や敵の弾にぶつかるとダメージ");
		DrawFormatString(memo[4][0], memo[4][1], GetColor(0, 0, 0), "ハート体力回復\n$お金が手に入る");
		DrawFormatString(memo[5][0], memo[5][1], GetColor(0, 0, 0), "左上の単位必要数まで単位を集めるとステージクリア\n次のステージに進めるようになる\n※クリアした後に死んでもクリアしたことになります。");
	}
	if (genzainosutezi == 8) {
		DrawFormatString(memo[0][0], memo[0][1], GetColor(0, 0, 0), "Welcome to the hell!!\n");
		DrawFormatString(memo[1][0], memo[1][1], GetColor(0, 0, 0), "ここから先は、半端ない難易度でステージを作っていきます。");
		DrawFormatString(memo[2][0], memo[2][1], GetColor(0, 0, 0), "むりげーになったらごめんなさい");
		DrawFormatString(memo[3][0], memo[3][1], GetColor(0, 0, 0), "あと、ステージの設定は適当にやってます。");
		DrawFormatString(memo[4][0], memo[4][1], GetColor(0, 0, 0), "俺に単位を!!");
		DrawFormatString(memo[5][0], memo[5][1], GetColor(0, 0, 0), "ステージは今のところ14ステージまであります。");
	}
	if (CheckHitKey(KEY_INPUT_Z) == 1)
		for (i = 0; i < k; i++) {
			DrawFormatString(0, i * 20 + 20, GetColor(255, 255, 255), "%d,X(%d～%d)Y(%d～%d)", i, kabeL[i][0][0], kabeL[i][0][1],
				kabeL[i][1][0], kabeL[i][1][1]);
		}
	if (CheckHitKey(KEY_INPUT_X) == 1)
		for (m = 0; m < 20; m++) {
			DrawFormatString(0, m * 20 + 20, GetColor(255, 0, 0), "%d,X(%d～%d)Y(%d～%d)", m, kabeD[m][0][0], kabeD[m][0][1],
				kabeD[m][1][0], kabeD[m][1][1]);
		}
	
	
	
		DrawFormatString(290, 210, GetColor(255, 0, 0), "(X;%d,Y;%d,)", -kabeL[0][0][0] + 290, -kabeL[0][1][0] + 210);
		if (tannihituyousuu > genzainotanninokazu) {//単位の必要数を表示
			DrawFormatString(0, 0, GetColor(255, 255, 255), "単位;%d/%d,", genzainotanninokazu, tannihituyousuu);
		}
		else if (tannihituyousuu <= tannihituyousuu) {
			DrawFormatString(0, 0, GetColor(255, 255, 255), "単位;%d/%d,\nステージクリア!!\nENTERでメニュー画面へ戻る", genzainotanninokazu, tannihituyousuu);
			if (genzainosutezi >= sutezinosaidaiti) { sutezinosaidaiti++; }
		}

		DrawFormatString(100, 0, GetColor(255, 255, 255), "お金;%d", okane);
		DrawFormatString(220, 200, GetColor(255, 255, 255), "左クリックでゲームスタート");

		
		/*DrawFormatString(100, 100, GetColor(255, 255, 255), "X(%d)Y(%d),距離二乗%d,kaiten%d,左%d中%d右%d", mausux, mausuy,
		((mausux - 320)*(mausux - 320) + (mausuy - 240)*(mausuy - 240)),
		mausukaiten,mausuhidari,mausumannnaka,mausumigi);//*/
		//DrawFormatString(100, 100, GetColor(255, 255, 255), "%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f", ututeki[0][0], ututeki[0][1], ututeki[0][2], ututeki[0][3], ututeki[0][4], ututeki[0][5], ututeki[0][6], ututeki[0][7], ututeki[0][8], ututeki[0][9], ututeki[0][10], ututeki[0][11], ututeki[0][12] );

		DrawBox(640 - tairyokusaidaiti - 2, 470, 640, 480, GetColor(0, 0, 0), TRUE);    // 四角形を描画 
		if (tairyoku >= 1) {
			DrawBox(640 - tairyoku - 1, 471, 639, 479, GetColor(0, 255, 0), TRUE);
		}
		DrawBox(588, 461, 640, 471, (0, 0, 0), TRUE);    // 四角形を描画
		if (mausuhidari <= 49 && mausuhidari >= 0) { DrawBox(639 - mausuhidari, 462, 639, 470, GetColor(255, 255, 0), TRUE); }
		if (mausuhidari <= 99 && mausuhidari >= 50) { DrawBox(639 - mausuhidari + 50, 462, 639, 470, GetColor(255, 100, 0), TRUE); }
		if (mausuhidari >= 100) { DrawBox(589, 462, 639, 470, GetColor(255, 0, 0), TRUE); }
		if (tairyoku <= 0) {
			DrawFormatString(220, 225, GetColor(0, 0, 0), "ENTERでメニュー画面に戻る");
		}
		//DrawFormatString(x, (y - 10), GetColor(255, 255, 255), "(%d,%d)", x, y);
		ScreenFlip();
	}














	//本編
	while (1)
	{
		if (ProcessMessage() != 0 || CheckHitKey(KEY_INPUT_ESCAPE) == 1||genzainosutezi==0)
			break;
		if (CheckHitKey(KEY_INPUT_NUMPADENTER) == 1)
		{
			genzainosutezi = 0;
			break;
		}
		genzainozikan++;
		for (kurikaesi = 0; kurikaesi++; kurikaesi < 18) {
			utimakuruteki[kurikaesi][4] = 0; utimakuruteki[kurikaesi][24] = 0; utimakuruteki[kurikaesi][25] = 0; utimakuruteki[kurikaesi][26] = 0; utimakuruteki[kurikaesi][27] = 0;
		}
		if (genzainosutezi == 2) {
			//ダメージ壁の移動用のプログラム
			if (kabeDidou1 <= 640) {
				kabeDidou1++;
			}
			else { kabeDidou1 = 0; }
			if (kabeDidou1 <= 160 && kabeDidou1 >= 0) {
				kabeD[0][0][0] -= 1;
				kabeD[0][0][1] -= 1;
			}
			if (kabeDidou1 <= 320 && kabeDidou1 >= 160) {
				kabeD[0][1][0] += 1;
				kabeD[0][1][1] += 1;
			}
			if (kabeDidou1 <= 480 && kabeDidou1 >= 320) {
				kabeD[0][0][0] += 1;
				kabeD[0][0][1] += 1;
			}
			if (kabeDidou1 <= 640 && kabeDidou1 >= 480) {
				kabeD[0][1][0] -= 1;
				kabeD[0][1][1] -= 1;
			}

			for (kabeDidou[7] = 0; kabeDidou[7] < 7; kabeDidou[7]++) {
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 4) {
					kabeDidou[kabeDidou[7]]++;
				}
				else { kabeDidou[kabeDidou[7]] = 0; }
			}
			for (kabeDidou[7] = 0; kabeDidou[7] < 7; kabeDidou[7]++) {
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) && kabeDidou[kabeDidou[7]] >= 0) {
					kabeD[kabeDidou[7] + 3][0][0] += 5;
					kabeD[kabeDidou[7] + 3][0][1] += 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 2 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7])) {
					kabeD[kabeDidou[7] + 3][1][0] += 5;
					kabeD[kabeDidou[7] + 3][1][1] += 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 3 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7]) * 2) {
					kabeD[kabeDidou[7] + 3][0][0] -= 5;
					kabeD[kabeDidou[7] + 3][0][1] -= 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 4 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7]) * 3) {
					kabeD[kabeDidou[7] + 3][1][0] -= 5;
					kabeD[kabeDidou[7] + 3][1][1] -= 5;
				}
			}
		}
		/*
		if (genzainosutezi == 2) {
			//ダメージ壁の移動用のプログラム
			if (kabeDidou1 <= 320) {
				kabeDidou1++;
			}
			else { kabeDidou1 = 0; }
			if (kabeDidou1 <= 80 && kabeDidou1 >= 0) {
				kabeD[0][0][0] -= 1;
				kabeD[0][0][1] -= 1;
			}
			if (kabeDidou1 <= 160 && kabeDidou1 >= 80) {
				kabeD[0][1][0] += 1;
				kabeD[0][1][1] += 1;
			}
			if (kabeDidou1 <= 240 && kabeDidou1 >= 160) {
				kabeD[0][0][0] -= 1;
				kabeD[0][0][1] -= 1;
			}
			if (kabeDidou1 <= 320 && kabeDidou1 >= 240) {
				kabeD[0][1][0] += 1;
				kabeD[0][1][1] += 1;
			}

			for (kabeDidou[7] = 0; kabeDidou[7] < 7; kabeDidou[7]++) {
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 4) {
					kabeDidou[kabeDidou[7]]++;
				}
				else { kabeDidou[kabeDidou[7]] = 0; }
			}
			for (kabeDidou[7] = 0; kabeDidou[7] < 7; kabeDidou[7]++) {
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) && kabeDidou[kabeDidou[7]] >= 0) {
					kabeD[kabeDidou[7] + 3][0][0] += 5;
					kabeD[kabeDidou[7] + 3][0][1] += 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 2 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7])) {
					kabeD[kabeDidou[7] + 3][1][0] += 5;
					kabeD[kabeDidou[7] + 3][1][1] += 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 3 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7]) * 2) {
					kabeD[kabeDidou[7] + 3][0][0] -= 5;
					kabeD[kabeDidou[7] + 3][0][1] -= 5;
				}
				if (kabeDidou[kabeDidou[7]] <= (88 - 12 * kabeDidou[7]) * 4 && kabeDidou[kabeDidou[7]] >= (88 - 12 * kabeDidou[7]) * 3) {
					kabeD[kabeDidou[7] + 3][1][0] -= 5;
					kabeD[kabeDidou[7] + 3][1][1] -= 5;
				}
			}
		}
		*/

		if (genzainosutezi == 3) {
			//3100カウント後に4方向からダメージ壁を移動させるための設定
			if (genzainozikan == 3100) {
				kabeD[0][0][0] += 3100;
				kabeD[0][0][1] += 3100;
				
				kabeD[1][0][0] += 3100;
				kabeD[1][0][1] += 3100;
				
				kabeD[2][0][0] += 3100;
				kabeD[2][0][1] += 3100;
				
				kabeD[3][0][0] += 3100;
				kabeD[3][0][1] += 3100;
				
				kabeD[4][1][0] -= 2500;
				kabeD[4][1][1] -= 2500;
				
				
				kabeD[5][1][0] -= 2500;
				kabeD[5][1][1] -= 2500;
				
				kabeD[6][1][0] -= 2500;
				kabeD[6][1][1] -= 2500;
				
				kabeD[7][1][0] -= 2500;
				kabeD[7][1][1] -= 2500;
				
				kabeD[8][0][0] -= 1900;
				kabeD[8][0][1] -= 1900;
				
				kabeD[9][0][0] -= 1900;
				kabeD[9][0][1] -= 1900;
				
				kabeD[10][0][0] -= 1900;
				kabeD[10][0][1] -= 1900;
				
				kabeD[11][0][0] -= 1900;
				kabeD[11][0][1] -= 1900;
				
				
				kabeD[12][1][0] += 1300;
				kabeD[12][1][1] += 1300;
				
				kabeD[13][1][0] += 1300;
				kabeD[13][1][1] += 1300;
				
				kabeD[14][1][0] += 1300;
				kabeD[14][1][1] += 1300;
				
				kabeD[15][1][0] += 1300;
				kabeD[15][1][1] += 1300;
			}
			if (genzainozikan <= 4600) {
				tannikabe[0][1][0]++;
				tannikabe[0][1][1]++;
			}

			//ダメージ壁の移動の設定
			for (kurikaesi = 0; kurikaesi < 4; kurikaesi++) { kabeD[kurikaesi][0][0]--; kabeD[kurikaesi][0][1]--; }
			for (kurikaesi = 4; kurikaesi < 8; kurikaesi++) { kabeD[kurikaesi][1][0]++; kabeD[kurikaesi][1][1]++; }
			for (kurikaesi = 8; kurikaesi < 12; kurikaesi++) { kabeD[kurikaesi][0][0]++; kabeD[kurikaesi][0][1]++; }
			for (kurikaesi = 12; kurikaesi < 16; kurikaesi++) { kabeD[kurikaesi][1][0]--; kabeD[kurikaesi][1][1]--; }
		}

		if (genzainosutezi == 5) {
			tannikabe[0][1][1] ++; tannikabe[0][1][0] ++;
		}
		if (genzainosutezi == 4) {
			if (zakoteki[0][5] == -10000 && sutezinogimikku == 0) 
			{
				zakoteki[1][0] = 160; zakoteki[1][1] = 80; zakoteki[1][3] = 0; zakoteki[1][4] = 0; zakoteki[1][5] = 700; 
				zakoteki[2][0] = 480; zakoteki[2][1] = 400; zakoteki[2][3] = 0; zakoteki[2][4] = 0; zakoteki[2][5] = 700;
				sutezinogimikku = 1;
			}
			if (zakoteki[1][5] == -10000 && zakoteki[2][5] == -10000 && sutezinogimikku == 1)
			{
				zakoteki[3][0] = 160; zakoteki[3][1] = 80; zakoteki[3][3] = 0; zakoteki[3][4] = 0; zakoteki[3][5] = 500;
				zakoteki[4][0] = 160; zakoteki[4][1] = 400; zakoteki[4][3] = 0; zakoteki[4][4] = 0; zakoteki[4][5] = 500;
				zakoteki[5][0] = 480; zakoteki[5][1] = 400; zakoteki[5][3] = 0; zakoteki[5][4] = 0; zakoteki[5][5] = 500;
				zakoteki[6][0] = 480; zakoteki[6][1] = 80; zakoteki[6][3] = 0; zakoteki[6][4] = 0; zakoteki[6][5] = 500;
				sutezinogimikku = 2;
			}
			if (zakoteki[3][5] == -10000 && zakoteki[4][5] == -10000 && zakoteki[5][5] == -10000 && zakoteki[6][5] == -10000 && sutezinogimikku == 2)
			{
				zakoteki[7][0] = 160; zakoteki[7][1] = 80; zakoteki[7][3] = 0; zakoteki[7][4] = 0; zakoteki[7][5] = 300;
				zakoteki[8][0] = 160; zakoteki[8][1] = 240; zakoteki[8][3] = 0; zakoteki[8][4] = 0; zakoteki[8][5] = 300;
				zakoteki[9][0] = 160; zakoteki[9][1] = 400; zakoteki[9][3] = 0; zakoteki[9][4] = 0; zakoteki[9][5] = 300; 
				zakoteki[10][0] = 320; zakoteki[10][1] = 400; zakoteki[10][3] = 0; zakoteki[10][4] = 0; zakoteki[10][5] = 300;
				zakoteki[11][0] = 480; zakoteki[11][1] = 400; zakoteki[11][3] = 0; zakoteki[11][4] = 0; zakoteki[11][5] = 300;
				zakoteki[12][0] = 480; zakoteki[12][1] = 240; zakoteki[12][3] = 0; zakoteki[12][4] = 0; zakoteki[12][5] = 300;
				zakoteki[13][0] = 480; zakoteki[13][1] = 80; zakoteki[13][3] = 0; zakoteki[13][4] = 0; zakoteki[13][5] = 300;
				zakoteki[14][0] = 320; zakoteki[14][1] = 80; zakoteki[14][3] = 0; zakoteki[14][4] = 0; zakoteki[14][5] = 300;
				sutezinogimikku = 3;
			}
			if (zakoteki[7][5] == -10000 && zakoteki[8][5] == -10000 && zakoteki[9][5] == -10000 && zakoteki[10][5] == -10000 && zakoteki[11][5] == -10000 && zakoteki[12][5] == -10000 && zakoteki[13][5] == -10000 && zakoteki[14][5] == -10000 && sutezinogimikku == 3)
			{
				genzainotanninokazu = 1; sutezinogimikku = 4;
			}
		
		
		}
		//移動したときの設定。もっと効率の良い方法がありそうな気がする...
		if (CheckHitKey(KEY_INPUT_A) == 1&&tairyoku>0) {
			for (i = 0; i < k; i++) {
				kabeL[i][0][0] = kabeL[i][0][0] + sokudo;
				kabeL[i][0][1] = kabeL[i][0][1] + sokudo;
			}
			for (m = 0; m < n; m++) {
				kabeD[m][0][0] = kabeD[m][0][0] + sokudo;
				kabeD[m][0][1] = kabeD[m][0][1] + sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
				kuroikabe[kurikaesi][0][0] +=sokudo;
				kuroikabe[kurikaesi][0][1] +=sokudo;
			}
			for (p = 0; p < tanninokazu; p++) {
				tannikabe[p][0][0] = tannikabe[p][0][0] + sokudo;
				tannikabe[p][0][1] = tannikabe[p][0][1] + sokudo;
			}
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				tama[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
			tametama[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
				zakoteki[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][7] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
				utimakuruteki[kurikaesi][0] += sokudo;
				utimakuruteki[kurikaesi][7] += sokudo;
				utimakuruteki[kurikaesi][12] += sokudo;
				utimakuruteki[kurikaesi][18] += sokudo;
				utimakuruteki[kurikaesi][20] += sokudo;
				utimakuruteki[kurikaesi][22] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
				dekaiteki[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
				memo[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
				kaihukuaitemu[kurikaesi][0] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
				okaneaitemu[kurikaesi][0] += sokudo;
			}
		}
		if (CheckHitKey(KEY_INPUT_D) == 1 && tairyoku>0) {
			for (i = 0; i < k; i++) {
				kabeL[i][0][0] = kabeL[i][0][0] - sokudo;
				kabeL[i][0][1] = kabeL[i][0][1] - sokudo;
			}
			for (m = 0; m < n; m++) {
				kabeD[m][0][0] = kabeD[m][0][0] - sokudo;
				kabeD[m][0][1] = kabeD[m][0][1] - sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
				kuroikabe[kurikaesi][0][0] -= sokudo;
				kuroikabe[kurikaesi][0][1] -= sokudo;
			}
			for (p = 0; p < tanninokazu; p++) {
				tannikabe[p][0][0] = tannikabe[p][0][0] - sokudo;
				tannikabe[p][0][1] = tannikabe[p][0][1] - sokudo;
			}
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				tama[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				tametama[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
				zakoteki[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][7] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
				utimakuruteki[kurikaesi][0] -= sokudo;
				utimakuruteki[kurikaesi][7] -= sokudo;
				utimakuruteki[kurikaesi][12] -= sokudo;
				utimakuruteki[kurikaesi][18] -= sokudo;
				utimakuruteki[kurikaesi][20] -= sokudo;
				utimakuruteki[kurikaesi][22] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
				dekaiteki[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
				memo[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
				kaihukuaitemu[kurikaesi][0] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
				okaneaitemu[kurikaesi][0] -= sokudo;
			}

		}
		if (CheckHitKey(KEY_INPUT_W) == 1 && tairyoku>0) {
			for (i = 0; i < k; i++) {
				kabeL[i][1][0] = kabeL[i][1][0] + sokudo;
				kabeL[i][1][1] = kabeL[i][1][1] + sokudo;
			}
			for (m = 0; m < n; m++) {
				kabeD[m][1][0] = kabeD[m][1][0] + sokudo;
				kabeD[m][1][1] = kabeD[m][1][1] + sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
				kuroikabe[kurikaesi][1][0] += sokudo;
				kuroikabe[kurikaesi][1][1] += sokudo;
			}
			for (p = 0; p < tanninokazu; p++) {
				tannikabe[p][1][0] = tannikabe[p][1][0] + sokudo;
				tannikabe[p][1][1] = tannikabe[p][1][1] + sokudo;
			}
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				tama[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
			tametama[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
				zakoteki[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][8] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
				utimakuruteki[kurikaesi][1] += sokudo;
				utimakuruteki[kurikaesi][8] += sokudo;
				utimakuruteki[kurikaesi][13] += sokudo;
				utimakuruteki[kurikaesi][19] += sokudo;
				utimakuruteki[kurikaesi][21] += sokudo;
				utimakuruteki[kurikaesi][23] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
				dekaiteki[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
				memo[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
				kaihukuaitemu[kurikaesi][1] += sokudo;
			}
			for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
				okaneaitemu[kurikaesi][1] += sokudo;
			}
		}
		if (CheckHitKey(KEY_INPUT_S) == 1 && tairyoku>0) {
			for (i = 0; i < k; i++) {
				kabeL[i][1][0] = kabeL[i][1][0] - sokudo;
				kabeL[i][1][1] = kabeL[i][1][1] - sokudo;
			}
			for (m = 0; m < n; m++) {
				kabeD[m][1][0] = kabeD[m][1][0] - sokudo;
				kabeD[m][1][1] = kabeD[m][1][1] - sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
				kuroikabe[kurikaesi][1][0] -= sokudo;
				kuroikabe[kurikaesi][1][1] -= sokudo;
			}
			for (p = 0; p < tanninokazu; p++) {
				tannikabe[p][1][0] = tannikabe[p][1][0] - sokudo;
				tannikabe[p][1][1] = tannikabe[p][1][1] - sokudo;
			}
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				tama[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				tametama[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
				zakoteki[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				ututeki[kurikaesi][8] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
				utimakuruteki[kurikaesi][1] -= sokudo;
				utimakuruteki[kurikaesi][8] -= sokudo;
				utimakuruteki[kurikaesi][13] -= sokudo;
				utimakuruteki[kurikaesi][19] -= sokudo;
				utimakuruteki[kurikaesi][21] -= sokudo;
				utimakuruteki[kurikaesi][23] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
				dekaiteki[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
				memo[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
				kaihukuaitemu[kurikaesi][1] -= sokudo;
			}
			for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
				okaneaitemu[kurikaesi][1] -= sokudo;
			}
		}
		
		//壁に当たって動かないときにほかのものが無駄に動かないようにするプログラム
		for (i = 0; i < k; i++) {
			if (kabeL[i][0][0] < 325 && kabeL[i][0][0] > 315 && kabeL[i][1][0] < 245 && kabeL[i][1][1] > 235) {
				for (kurikaesi = 0; kurikaesi < k; kurikaesi++) {
					kabeL[kurikaesi][0][0] = kabeL[kurikaesi][0][0] + sokudo;
					kabeL[kurikaesi][0][1] = kabeL[kurikaesi][0][1] + sokudo;
				}
				for (m = 0; m < n; m++) {
					kabeD[m][0][0] = kabeD[m][0][0] + sokudo;
					kabeD[m][0][1] = kabeD[m][0][1] + sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
					kuroikabe[kurikaesi][0][0] += sokudo;
					kuroikabe[kurikaesi][0][1] += sokudo;
				}
				for (p = 0; p < tanninokazu; p++) {
					tannikabe[p][0][0] = tannikabe[p][0][0] + sokudo;
					tannikabe[p][0][1] = tannikabe[p][0][1] + sokudo;
				}
				for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
					tama[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
					tametama[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
					zakoteki[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][7] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					utimakuruteki[kurikaesi][0] += sokudo;
					utimakuruteki[kurikaesi][7] += sokudo;
					utimakuruteki[kurikaesi][12] += sokudo;
					utimakuruteki[kurikaesi][18] += sokudo;
					utimakuruteki[kurikaesi][20] += sokudo;
					utimakuruteki[kurikaesi][22] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
					dekaiteki[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
					memo[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
					kaihukuaitemu[kurikaesi][0] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
					okaneaitemu[kurikaesi][0] += sokudo;
				}
			}
		}

		for (i = 0; i < k; i++) {
			if (kabeL[i][0][1] < 325 && kabeL[i][0][1] > 315 && kabeL[i][1][0] < 245 && kabeL[i][1][1] > 235) {
				for (kurikaesi = 0; kurikaesi < k; kurikaesi++) {
					kabeL[kurikaesi][0][0] = kabeL[kurikaesi][0][0] - sokudo;
					kabeL[kurikaesi][0][1] = kabeL[kurikaesi][0][1] - sokudo;
				}
				for (m = 0; m < n; m++) {
					kabeD[m][0][0] = kabeD[m][0][0] - sokudo;
					kabeD[m][0][1] = kabeD[m][0][1] - sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
					kuroikabe[kurikaesi][0][0] -= sokudo;
					kuroikabe[kurikaesi][0][1] -= sokudo;
				}
				for (p = 0; p < tanninokazu; p++) {
					tannikabe[p][0][0] = tannikabe[p][0][0] - sokudo;
					tannikabe[p][0][1] = tannikabe[p][0][1] - sokudo;
				}
				for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
					tama[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				tametama[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
					zakoteki[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][7] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					utimakuruteki[kurikaesi][0] -= sokudo;
					utimakuruteki[kurikaesi][7] -= sokudo;
					utimakuruteki[kurikaesi][12] -= sokudo;
					utimakuruteki[kurikaesi][18] -= sokudo;
					utimakuruteki[kurikaesi][20] -= sokudo;
					utimakuruteki[kurikaesi][22] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
					dekaiteki[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
					memo[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
					kaihukuaitemu[kurikaesi][0] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
					okaneaitemu[kurikaesi][0] -= sokudo;
				}
			}
		}
		for (i = 0; i < k; i++) {
			if (kabeL[i][0][0] < 325 && kabeL[i][0][1] > 315 && kabeL[i][1][0] < 245 && kabeL[i][1][0] > 235) {
				for (kurikaesi = 0; kurikaesi < k; kurikaesi++) {
					kabeL[kurikaesi][1][0] = kabeL[kurikaesi][1][0] + sokudo;
					kabeL[kurikaesi][1][1] = kabeL[kurikaesi][1][1] + sokudo;
				}
				for (m = 0; m < n; m++) {
					kabeD[m][1][0] = kabeD[m][1][0] + sokudo;
					kabeD[m][1][1] = kabeD[m][1][1] + sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
					kuroikabe[kurikaesi][1][0] += sokudo;
					kuroikabe[kurikaesi][1][1] += sokudo;
				}
				for (p = 0; p < tanninokazu; p++) {
					tannikabe[p][1][0] = tannikabe[p][1][0] + sokudo;
					tannikabe[p][1][1] = tannikabe[p][1][1] + sokudo;
				}
				for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
					tama[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				tametama[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
					zakoteki[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][8] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					utimakuruteki[kurikaesi][1] += sokudo;
					utimakuruteki[kurikaesi][8] += sokudo;
					utimakuruteki[kurikaesi][13] += sokudo;
					utimakuruteki[kurikaesi][19] += sokudo;
					utimakuruteki[kurikaesi][21] += sokudo;
					utimakuruteki[kurikaesi][23] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
					dekaiteki[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
					memo[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
					kaihukuaitemu[kurikaesi][1] += sokudo;
				}
				for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
					okaneaitemu[kurikaesi][1] += sokudo;
				}
			}
		}
		for (i = 0; i < k; i++) {
			if (kabeL[i][0][0] < 325 && kabeL[i][0][1] > 315 && kabeL[i][1][1] < 245 && kabeL[i][1][1] > 235) {
				for (kurikaesi = 0; kurikaesi < k; kurikaesi++) {
					kabeL[kurikaesi][1][0] = kabeL[kurikaesi][1][0] - sokudo;
					kabeL[kurikaesi][1][1] = kabeL[kurikaesi][1][1] - sokudo;
				}
				for (m = 0; m < n; m++) {
					kabeD[m][1][0] = kabeD[m][1][0] - sokudo;
					kabeD[m][1][1] = kabeD[m][1][1] - sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
					kuroikabe[kurikaesi][1][0] -= sokudo;
					kuroikabe[kurikaesi][1][1] -= sokudo;
				}
				for (p = 0; p < tanninokazu; p++) {
					tannikabe[p][1][0] = tannikabe[p][1][0] - sokudo;
					tannikabe[p][1][1] = tannikabe[p][1][1] - sokudo;
				}
				for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
					tama[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				tametama[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
					zakoteki[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					ututeki[kurikaesi][8] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					utimakuruteki[kurikaesi][1] -= sokudo;
					utimakuruteki[kurikaesi][8] -= sokudo;
					utimakuruteki[kurikaesi][13] -= sokudo;
					utimakuruteki[kurikaesi][19] -= sokudo;
					utimakuruteki[kurikaesi][21] -= sokudo;
					utimakuruteki[kurikaesi][23] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
					dekaiteki[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < memonokazu; kurikaesi++) {
					memo[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
					kaihukuaitemu[kurikaesi][1] -= sokudo;
				}
				for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
					okaneaitemu[kurikaesi][1] -= sokudo;
				}
			}
		}
		//ダメージ壁のあたり判定
		if (muteki >= 30) {
			for (m = 0; m < n; m++) {
				if (kabeD[m][0][0] < 325 && kabeD[m][0][0] > 315 && kabeD[m][1][0] < 245 && kabeD[m][1][1] > 235) {
					tairyoku-=damezikabenokougekiryoku; muteki = 0;
				}
				else if (kabeD[m][0][1] < 325 && kabeD[m][0][1] > 315 && kabeD[m][1][0] < 245 && kabeD[m][1][1] > 235) {
					tairyoku -= damezikabenokougekiryoku; muteki = 0;
				}
				else if (kabeD[m][0][0] < 325 && kabeD[m][0][1] > 315 && kabeD[m][1][0] < 245 && kabeD[m][1][0] > 235) {
					tairyoku -= damezikabenokougekiryoku; muteki = 0;
				}
				else if (kabeD[m][0][0] < 325 && kabeD[m][0][1] > 315 && kabeD[m][1][1] < 245 && kabeD[m][1][1] > 235) {
					tairyoku -= damezikabenokougekiryoku; muteki = 0;
				}
				else if (kabeD[m][0][0] < 325 && kabeD[m][0][1] > 315 && kabeD[m][1][0] < 245 && kabeD[m][1][1] > 235) {
					tairyoku -= damezikabenokougekiryoku; muteki = 0;
				}
			}
		}
		if(muteki<=29){ muteki++; }
		
		//黒い壁のあたり判定の設定
		for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++) {
			if (kuroikabe[kurikaesi][0][0] < 325 && kuroikabe[kurikaesi][0][0] > 315 && kuroikabe[kurikaesi][1][0] < 245 && kuroikabe[kurikaesi][1][1] > 235) {
				tairyoku = 0;
			}
			else if (kuroikabe[kurikaesi][0][1] < 325 && kuroikabe[kurikaesi][0][1] > 315 && kuroikabe[kurikaesi][1][0] < 245 && kuroikabe[kurikaesi][1][1] > 235) {
				tairyoku = 0;
			}
			else if (kuroikabe[kurikaesi][0][0] < 325 && kuroikabe[kurikaesi][0][1] > 315 && kuroikabe[kurikaesi][1][0] < 245 && kuroikabe[kurikaesi][1][0] > 235) {
				tairyoku = 0;
			}
			else if (kuroikabe[kurikaesi][0][0] < 325 && kuroikabe[kurikaesi][0][1] > 315 && kuroikabe[kurikaesi][1][1] < 245 && kuroikabe[kurikaesi][1][1] > 235) {
				tairyoku = 0;
			}
			else if (kuroikabe[kurikaesi][0][0] < 325 && kuroikabe[kurikaesi][0][1] > 315 && kuroikabe[kurikaesi][1][0] < 245 && kuroikabe[kurikaesi][1][1] > 235) {
				tairyoku = 0;
			}
		}
		//回復アイテムのあたり判定。
		for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
			if (kaihukuaitemu[kurikaesi][3] == 1) {
				if (kaihukuaitemu[kurikaesi][0] - 5 < 325 && kaihukuaitemu[kurikaesi][0] - 5 > 315 && kaihukuaitemu[kurikaesi][1] - 5< 245 && kaihukuaitemu[kurikaesi][1] + 5 > 235) {
					//回復アイテムの左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
					tairyoku += kaihukuaitemu[kurikaesi][2];
					kaihukuaitemu[kurikaesi][3]=0;
					PlaySoundMem(koukaonkaihukuaitemu, DX_PLAYTYPE_BACK);
				}
				else if (kaihukuaitemu[kurikaesi][0] + 5 < 325 && kaihukuaitemu[kurikaesi][0] + 5 > 315 && kaihukuaitemu[kurikaesi][1] - 5 < 245 && kaihukuaitemu[kurikaesi][1] + 5 > 235) {
					//回復アイテムの右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
					tairyoku += kaihukuaitemu[kurikaesi][2];
					kaihukuaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonkaihukuaitemu, DX_PLAYTYPE_BACK);
				}
				else if (kaihukuaitemu[kurikaesi][0] - 5 < 325 && kaihukuaitemu[kurikaesi][0] + 5 > 315 && kaihukuaitemu[kurikaesi][1] - 5 < 245 && kaihukuaitemu[kurikaesi][1] - 5 > 235) {
					//回復アイテムの上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
					tairyoku += kaihukuaitemu[kurikaesi][2];
					kaihukuaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonkaihukuaitemu, DX_PLAYTYPE_BACK);
				}
				else if (kaihukuaitemu[kurikaesi][0] - 5 < 325 && kaihukuaitemu[kurikaesi][0] + 5 > 315 && kaihukuaitemu[kurikaesi][1] + 5 < 245 && kaihukuaitemu[kurikaesi][1] + 5 > 235) {
					//回復アイテムの下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
					tairyoku += kaihukuaitemu[kurikaesi][2];
					kaihukuaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonkaihukuaitemu, DX_PLAYTYPE_BACK);
				}
			}
		}
		//もし体力が体力の最大値を超えているとき、体力を体力の最大値と同じにする設定。
		if (tairyoku > tairyokusaidaiti) { tairyoku = tairyokusaidaiti; }
		//前回の体力が現在の体力より減っていたら音を鳴らす設定。
		if (tairyoku < tairyokuzenkai&&(tairyoku>0)) { PlaySoundMem(koukaondamezikuratta, DX_PLAYTYPE_BACK); }
		if (tairyoku <= 0 && tairyokuzenkai > 0) { PlaySoundMem(koukaongemuoba, DX_PLAYTYPE_BACK); }
		tairyokuzenkai = tairyoku;
		//お金アイテムのあたり判定。
		for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
			if (okaneaitemu[kurikaesi][3] == 1) {
				if (okaneaitemu[kurikaesi][0] - 5 < 325 && okaneaitemu[kurikaesi][0] - 5 > 315 && okaneaitemu[kurikaesi][1] - 5< 245 && okaneaitemu[kurikaesi][1] + 5 > 235) {
					//お金アイテムの左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
					okane += okaneaitemu[kurikaesi][2];
					okanenosaidaiti += okaneaitemu[kurikaesi][2];
					okaneaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonokanewohirottatoki, DX_PLAYTYPE_BACK);
				}
				else if (okaneaitemu[kurikaesi][0] + 5 < 325 && okaneaitemu[kurikaesi][0] + 5 > 315 && okaneaitemu[kurikaesi][1] - 5 < 245 && okaneaitemu[kurikaesi][1] + 5 > 235) {
					//お金アイテムの右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
					okane += okaneaitemu[kurikaesi][2];
					okanenosaidaiti += okaneaitemu[kurikaesi][2];
					okaneaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonokanewohirottatoki, DX_PLAYTYPE_BACK);
				}
				else if (okaneaitemu[kurikaesi][0] - 5 < 325 && okaneaitemu[kurikaesi][0] + 5 > 315 && okaneaitemu[kurikaesi][1] - 5 < 245 && okaneaitemu[kurikaesi][1] - 5 > 235) {
					//お金アイテムの上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
					okane += okaneaitemu[kurikaesi][2];
					okanenosaidaiti += okaneaitemu[kurikaesi][2];
					okaneaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonokanewohirottatoki, DX_PLAYTYPE_BACK);
				}
				else if (okaneaitemu[kurikaesi][0] - 5 < 325 && okaneaitemu[kurikaesi][0] + 5 > 315 && okaneaitemu[kurikaesi][1] + 5 < 245 && okaneaitemu[kurikaesi][1] + 5 > 235) {
					//お金アイテムの下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
					okane += okaneaitemu[kurikaesi][2];
					okanenosaidaiti += okaneaitemu[kurikaesi][2];
					okaneaitemu[kurikaesi][3] = 0;
					PlaySoundMem(koukaonokanewohirottatoki, DX_PLAYTYPE_BACK);
				}
			}
		}

		//集める単位のあたり判定
		for (p = 0; p < tanninokazu; p++) {
			if ((tannikabe[p][0][0] < 325 && tannikabe[p][0][0] > 315 && tannikabe[p][1][0] < 245 && tannikabe[p][1][1] > 235&&tairyoku>0) ||
				(tannikabe[p][0][1] < 325 && tannikabe[p][0][1] > 315 && tannikabe[p][1][0] < 245 && tannikabe[p][1][1] > 235 && tairyoku>0) ||
				(tannikabe[p][0][0] < 325 && tannikabe[p][0][1] > 315 && tannikabe[p][1][0] < 245 && tannikabe[p][1][0] > 235 && tairyoku>0) ||
				(tannikabe[p][0][0] < 325 && tannikabe[p][0][1] > 315 && tannikabe[p][1][1] < 245 && tannikabe[p][1][1] > 235 && tairyoku>0)) {
				genzainotanninokazu += 1;
				tannikabe[p][0][0] = 10000000;
				tannikabe[p][0][1] = 10000000;
				tannikabe[p][1][0] = 10000000;
				tannikabe[p][1][1] = 10000000;//こんな方法で消すのは意味不明だけど今回はこれで許してください...一応ほかの方法があるけど設定するのがめんどくさかった。
				PlaySoundMem(koukaontanniwohirottatoki, DX_PLAYTYPE_BACK);
			}
		}
		//ここから溜め弾を撃つ設定(1段階目)
		if(mausuhidariutu>=10&&mausuhidariutu<=19 && tairyoku>0){
			
			
				if (mausuhidariutu == 10) {
					PlaySoundMem(koukaontametehassya, DX_PLAYTYPE_BACK);
					for (kurikaesi = 0; kurikaesi < 3; kurikaesi++) {
						tametama[kurikaesi][0] = 320;
						tametama[kurikaesi][1] = 240;
						tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
						tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 10 * (DX_PI / 180)*kurikaesi - 10 * (DX_PI / 180));
						tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 10 * (DX_PI / 180)*kurikaesi - 10 * (DX_PI / 180));
						tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
					}
				}
					if (mausuhidariutu == 15) {
						for (kurikaesi = 3; kurikaesi < 6; kurikaesi++) {
							tametama[kurikaesi][0] = 320;
							tametama[kurikaesi][1] = 240;
							tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
							tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 10 * (DX_PI / 180)*(kurikaesi-3) - 10 * (DX_PI / 180));
							tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 10 * (DX_PI / 180)*(kurikaesi-3) - 10 * (DX_PI / 180));
							tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
						}
				}
					mausuhidariutu++;
			}
		if (mausuhidariutu == 20) { mausuhidari = 0; mausuhidariutu = 0; mausuhidarizenkai = 0; }

		//ここから溜め弾を撃つ設定(2段階目)
		if (mausuhidariutu >= 30 && mausuhidariutu <= 49 && tairyoku>0) {


			if (mausuhidariutu == 30) {
				PlaySoundMem(koukaontametehassya, DX_PLAYTYPE_BACK);
				for (kurikaesi = 6; kurikaesi < 11; kurikaesi++) {
					tametama[kurikaesi][0] = 320;
					tametama[kurikaesi][1] = 240;
					tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
					tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi-6) - 10 * (DX_PI / 180));
					tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi-6) - 10 * (DX_PI / 180));
					tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
				}
			}
			if (mausuhidariutu == 35) {
				for (kurikaesi = 11; kurikaesi < 16; kurikaesi++) {
					tametama[kurikaesi][0] = 320;
					tametama[kurikaesi][1] = 240;
					tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
					tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 11) - 10 * (DX_PI / 180));
					tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 11) - 10* (DX_PI / 180));
					tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
				}
			}
			if (mausuhidariutu == 40) {
				for (kurikaesi = 16; kurikaesi < 21; kurikaesi++) {
					tametama[kurikaesi][0] = 320;
					tametama[kurikaesi][1] = 240;
					tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
					tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 16) - 10 * (DX_PI / 180));
					tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 16) - 10 * (DX_PI / 180));
					tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
				}
			}
			if (mausuhidariutu == 45) {
				for (kurikaesi = 21; kurikaesi < 26; kurikaesi++) {
					tametama[kurikaesi][0] = 320;
					tametama[kurikaesi][1] = 240;
					tametama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
					tametama[kurikaesi][2] = sin(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 21) - 10 * (DX_PI / 180));
					tametama[kurikaesi][3] = cos(tametama[kurikaesi][4] + 5 * (DX_PI / 180)*(kurikaesi - 21) - 10 * (DX_PI / 180));
					tametama[kurikaesi][6] = 1;//弾の表示をオンにする。
				}
			}
			mausuhidariutu++;
		}
		if (mausuhidariutu == 50) { mausuhidari = 0; mausuhidariutu = 0; mausuhidarizenkai = 0; }
		for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
			tametama[kurikaesi][0] += tametama[kurikaesi][3] * tamasokudo;
			tametama[kurikaesi][1] += tametama[kurikaesi][2] * tamasokudo;
		}


		//ここから通常弾を撃つ設定
		GetMousePoint(&mausux, &mausuy);//マウスの座標を取得する。
		
			if (tamazikan < tamakankaku * tamakazu) { tamazikan++; }
			else { tamazikan = 0; }
			
				for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++)
				{
					if (mausuhidari == 0 && tairyoku>0) {
					if (tamazikan == tamakankaku*kurikaesi) {
						tama[kurikaesi][0] = 320;
						tama[kurikaesi][1] = 240;
						tama[kurikaesi][4] = atan2((float)(-240 + mausuy), (float)(-320 + mausux));//ラジアンの値を出す魔法の計算式
						tama[kurikaesi][2] = sin(tama[kurikaesi][4]);
						tama[kurikaesi][3] = cos(tama[kurikaesi][4]);
						tama[kurikaesi][6] = 1;//弾の表示をオンにする。

					}
				}
				if (tamazikan == tamakankaku*kurikaesi + tamahikyori) {
					tama[kurikaesi][6] = 0;//tamahikyoriカウント後に弾の表示を消す。
				}
				if ((tamakazu*tamakankaku <= tamakankaku*kurikaesi + tamahikyori) && (tamazikan == -(tamakankaku*tamakazu) + (tamakankaku*kurikaesi + tamahikyori))) {
					tama[kurikaesi][6] = 0;//tamahikyoriカウント後に弾の表示を消す。ちなみにループの区切れのところ。
				}
				tama[kurikaesi][0] += tama[kurikaesi][3] * tamasokudo;
				tama[kurikaesi][1] += tama[kurikaesi][2] * tamasokudo;
			}
		
		//ここから弾が壁に当たったときに弾を無くす設定
		
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				for (i = 0; i < k; i++) {
					if (kabeL[i][0][0] < tama[kurikaesi][0] && kabeL[i][0][1] > tama[kurikaesi][0]
						&& kabeL[i][1][0] < tama[kurikaesi][1] && kabeL[i][1][1] > tama[kurikaesi][1]) {
						tama[kurikaesi][6] = 0;
					}
				}
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				for (i = 0; i < k; i++) {
					if (kabeL[i][0][0] < tametama[kurikaesi][0] && kabeL[i][0][1] > tametama[kurikaesi][0]
						&& kabeL[i][1][0] < tametama[kurikaesi][1] && kabeL[i][1][1] > tametama[kurikaesi][1]) {
						tametama[kurikaesi][6] = 0;
					}
				}
			}

		//ここから弾がザコ敵に当たったときの処理
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				for (i = 0; i < zakotekinokazu; i++) {
					if (zakoteki[i][0]-18 < tama[kurikaesi][0] && zakoteki[i][0] + 18 > tama[kurikaesi][0]
						&& zakoteki[i][1] - 18 < tama[kurikaesi][1] && zakoteki[i][1] + 18 > tama[kurikaesi][1]
						&&tama[kurikaesi][6]==1&&zakoteki[i][5]>0) {
						tama[kurikaesi][6] = 0;
						zakoteki[i][5]-=kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				for (i = 0; i < zakotekinokazu; i++) {
					if (zakoteki[i][0] - 18 < tametama[kurikaesi][0] && zakoteki[i][0] + 18 > tametama[kurikaesi][0]
						&& zakoteki[i][1] - 18 < tametama[kurikaesi][1] && zakoteki[i][1] + 18 > tametama[kurikaesi][1]
						&& tametama[kurikaesi][6] == 1 && zakoteki[i][5]>0) {
						tametama[kurikaesi][6] = 0;
						zakoteki[i][5]-=kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			//ここからザコ敵が体力0以下になったときにお金を足して、体力を－10000にする設定
			for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
				if (zakoteki[kurikaesi][5] <= 0 && zakoteki[kurikaesi][5] != -10000)
				{
					okane += zakoteki[kurikaesi][8]; okanenosaidaiti += zakoteki[kurikaesi][8]; zakoteki[kurikaesi][5] = -10000; PlaySoundMem(koukaonsindatoki, DX_PLAYTYPE_BACK);
				}
			}
			//ここから弾が撃つ敵に当たったときの処理
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				for (i = 0; i < ututekinokazu; i++) {
					if (ututeki[i][0] - 18 < tama[kurikaesi][0] && ututeki[i][0] + 18 > tama[kurikaesi][0]
						&& ututeki[i][1] - 18 < tama[kurikaesi][1] && ututeki[i][1] + 18 > tama[kurikaesi][1]
						&& tama[kurikaesi][6] == 1 && ututeki[i][5]>0) {
						tama[kurikaesi][6] = 0;
						ututeki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				for (i = 0; i < ututekinokazu; i++) {
					if (ututeki[i][0] - 18 < tametama[kurikaesi][0] && ututeki[i][0] + 18 > tametama[kurikaesi][0]
						&& ututeki[i][1] - 18 < tametama[kurikaesi][1] && ututeki[i][1] + 18 > tametama[kurikaesi][1]
						&& tametama[kurikaesi][6] == 1 && ututeki[i][5]>0) {
						tametama[kurikaesi][6] = 0;
						ututeki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			//ここから撃つ敵が体力0以下になったときにお金を足して、体力を－10000にする設定
			for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
				if (ututeki[kurikaesi][5] <= 0 && ututeki[kurikaesi][5] != -10000)
				{
					okane += ututeki[kurikaesi][10]; okanenosaidaiti += ututeki[kurikaesi][10]; ututeki[kurikaesi][5] = -10000; PlaySoundMem(koukaonsindatoki, DX_PLAYTYPE_BACK);
				}
			}
			//ここから弾が撃ちまくる敵に当たったときの処理
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				for (i = 0; i < utimakurutekinokazu; i++) {
					if (utimakuruteki[i][0] - 14 < tama[kurikaesi][0] && utimakuruteki[i][0] + 14 > tama[kurikaesi][0]
						&& utimakuruteki[i][1] - 14 < tama[kurikaesi][1] && utimakuruteki[i][1] + 14 > tama[kurikaesi][1]
						&& tama[kurikaesi][6] == 1 && utimakuruteki[i][5]>0) {
						tama[kurikaesi][6] = 0;
						utimakuruteki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				for (i = 0; i < utimakurutekinokazu; i++) {
					if (utimakuruteki[i][0] - 18 < tametama[kurikaesi][0] && utimakuruteki[i][0] + 18 > tametama[kurikaesi][0]
						&& utimakuruteki[i][1] - 18 < tametama[kurikaesi][1] && utimakuruteki[i][1] + 18 > tametama[kurikaesi][1]
						&& tametama[kurikaesi][6] == 1 && utimakuruteki[i][5]>0) {
						tametama[kurikaesi][6] = 0;
						utimakuruteki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			//ここから撃ちまくる敵が体力0以下になったときにお金を足して、体力を－10000にする設定
			for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
				if (utimakuruteki[kurikaesi][5] <= 0 && utimakuruteki[kurikaesi][5] != -10000)
				{
					okane += utimakuruteki[kurikaesi][10]; okanenosaidaiti += utimakuruteki[kurikaesi][10]; utimakuruteki[kurikaesi][5] = -10000; PlaySoundMem(koukaonsindatoki, DX_PLAYTYPE_BACK);
				}
			}
			//ここから弾がデカい敵に当たったときの処理
			for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
				for (i = 0; i < dekaitekinokazu; i++) {
					if (dekaiteki[i][0] - 36 < tama[kurikaesi][0] && dekaiteki[i][0] + 36 > tama[kurikaesi][0]
						&& dekaiteki[i][1] - 36 < tama[kurikaesi][1] && dekaiteki[i][1] + 36 > tama[kurikaesi][1]
						&& tama[kurikaesi][6] == 1 && dekaiteki[i][5]>0) {
						tama[kurikaesi][6] = 0;
						dekaiteki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			for (kurikaesi = 0; kurikaesi < 26; kurikaesi++) {
				for (i = 0; i < dekaitekinokazu; i++) {
					if (dekaiteki[i][0] - 36 < tametama[kurikaesi][0] && dekaiteki[i][0] + 36 > tametama[kurikaesi][0]
						&& dekaiteki[i][1] - 36 < tametama[kurikaesi][1] && dekaiteki[i][1] + 36 > tametama[kurikaesi][1]
						&& tametama[kurikaesi][6] == 1 && dekaiteki[i][5]>0) {
						tametama[kurikaesi][6] = 0;
						dekaiteki[i][5] -= kougekiryoku;
						PlaySoundMem(koukaondameziataeta, DX_PLAYTYPE_BACK);//ダメージを与えた時の音を鳴らす。
					}
				}
			}
			//ここからデカい敵が体力0以下になったときにお金を足して、体力を－10000にする設定
			for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
				if (dekaiteki[kurikaesi][5] <= 0 && dekaiteki[kurikaesi][5] != -10000)
				{
					okane += dekaiteki[kurikaesi][8]; okanenosaidaiti += dekaiteki[kurikaesi][8]; dekaiteki[kurikaesi][5] = -10000; PlaySoundMem(koukaonsindatoki, DX_PLAYTYPE_BACK);
				}
			}
		//ここからマウスの回転量を調べたりする設定
			
				//mausukaiten += GetMouseWheelRotVol();    //ホイール回転量取得(いらなくなりました...)
				//チャージ弾の設定。
				if (mausuhidariutu == 0) {
					if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 100) { mausuhidariutu = 30; tametamazikan2 = 0; }//30~50を使う。
					else if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 50) { mausuhidariutu = 10; tametamazikan1 = 0; }//10~20を使う。
					else if (mausuhidari == mausuhidarizenkai&&mausuhidari >= 1) 
					{ mausuhidariutu = 0; mausuhidari = 0; mausuhidarizenkai = 0; }
					mausuhidarizenkai = mausuhidari;
					if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && tairyoku>0)
						
					{
						mausuhidari++;
						// 押されている
					}
				}
				if (mausuhidari == 1&&mausuhidarizenkai==0&&genzainozikan>=4) { PlaySoundMem(koukaontamehazimetatoki, DX_PLAYTYPE_BACK); }
				if (mausuhidari == 50 && mausuhidarizenkai == 49) { PlaySoundMem(koukaontame1, DX_PLAYTYPE_BACK); }//溜めたときの音の設定
				if (mausuhidari == 100 && mausuhidarizenkai == 99) { PlaySoundMem(koukaontame2, DX_PLAYTYPE_BACK); }
				//溜め弾の時間を増やすのと溜め弾が50カウント後に消えるプログラム
				if (tametamazikan1 >= 0 && tametamazikan1 <= 55){ tametamazikan1++; }
				if (tametamazikan1 == 50) 
				{ for (kurikaesi = 0; kurikaesi < 3; kurikaesi++) { tametama[kurikaesi][6] = 0; } }
				if (tametamazikan1 == 55)
				{
					for (kurikaesi = 3; kurikaesi < 6; kurikaesi++) { tametama[kurikaesi][6] = 0; }
				}
				 tametamazikan2++; 
				if (tametamazikan2 == 50)
				{
					for (kurikaesi = 6; kurikaesi < 11; kurikaesi++) { tametama[kurikaesi][6] = 0; }
				}
				if (tametamazikan2 == 55)
				{
					for (kurikaesi = 11; kurikaesi < 16; kurikaesi++) { tametama[kurikaesi][6] = 0; }
				}
				if (tametamazikan2 == 60)
				{
					for (kurikaesi = 16; kurikaesi < 21; kurikaesi++) { tametama[kurikaesi][6] = 0; }
				}
				if (tametamazikan2 == 65)
				{
					for (kurikaesi = 21; kurikaesi < 26; kurikaesi++) { tametama[kurikaesi][6] = 0; }
				}

				/*if ((GetMouseInput() & MOUSE_INPUT_MIDDLE) != 0)
				{
					mausumannnaka++;
					// 押されている
				}
				if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
				{
					mausumigi++;
					// 押されている
				}*/
		
		//ここからザコ敵の設定
				for(kurikaesi=0;kurikaesi<zakotekinokazu;kurikaesi++){
					if (zakoteki[kurikaesi][5] > 0) {
						if (zakoteki[kurikaesi][3] == 0)
						{
							zakoteki[kurikaesi][2] = atan2((float)(240 - zakoteki[kurikaesi][1]), (float)(320 - zakoteki[kurikaesi][0]));
						//ラジアンの値を出す魔法の計算式
							
							zakoteki[kurikaesi][2] += ((GetRand(zakoteki[kurikaesi][11] * 2) - zakoteki[kurikaesi][11]) / 100)*(PI / 180);//ラジアンの値を多少ランダムにする設定
						}
						if (zakoteki[kurikaesi][3] >= zakoteki[kurikaesi][9]) {
							zakoteki[kurikaesi][3] = 0; zakoteki[kurikaesi][4] = 0;
						}
						else { zakoteki[kurikaesi][3]++; }
						
						if (zakoteki[kurikaesi][3] <= zakoteki[kurikaesi][9]/2) { zakoteki[kurikaesi][4] += zakoteki[kurikaesi][10]; }
						else { zakoteki[kurikaesi][4] -= zakoteki[kurikaesi][10]; }

						zakoteki[kurikaesi][0] += cos(zakoteki[kurikaesi][2])*zakoteki[kurikaesi][4];
						zakoteki[kurikaesi][1] += sin(zakoteki[kurikaesi][2])*zakoteki[kurikaesi][4];

					}
					}
				//ザコ敵の体当たりの攻撃の設定
				if (muteki >= 30) {
					for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
						if (zakoteki[kurikaesi][5] >= 1) {
							if (zakoteki[kurikaesi][0] - 18 < 325 && zakoteki[kurikaesi][0] - 18 > 315 && zakoteki[kurikaesi][1] - 18 < 245 && zakoteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= zakoteki[kurikaesi][7]; muteki = 0;
							}
							else if (zakoteki[kurikaesi][0] + 18 < 325 && zakoteki[kurikaesi][0] + 18 > 315 && zakoteki[kurikaesi][1] - 18 < 245 && zakoteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= zakoteki[kurikaesi][7]; muteki = 0;
							}
							else if (zakoteki[kurikaesi][0] - 18 < 325 && zakoteki[kurikaesi][0] + 18 > 315 && zakoteki[kurikaesi][1] - 18 < 245 && zakoteki[kurikaesi][1] - 18 > 235) {
								//ザコ敵の上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= zakoteki[kurikaesi][7]; muteki = 0;
							}
							else if (zakoteki[kurikaesi][0] - 18 < 325 && zakoteki[kurikaesi][0] + 18 > 315 && zakoteki[kurikaesi][1] + 18 < 245 && zakoteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= zakoteki[kurikaesi][7]; muteki = 0;
							}
							else if (zakoteki[kurikaesi][0] - 18 < 325 && zakoteki[kurikaesi][0] + 18 > 315 && zakoteki[kurikaesi][1] - 18 < 245 && zakoteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の壁が豆腐の内側の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= zakoteki[kurikaesi][7]; muteki = 0;
							}
						}
					}
				}

				//ここから撃つ敵の設定
				for (kurikaesi = 0; kurikaesi<ututekinokazu; kurikaesi++) {
					if (ututeki[kurikaesi][5] > 0) {
						//ラジアンの値を出す魔法の計算式
							ututeki[kurikaesi][2] = atan2((float)(240 - ututeki[kurikaesi][1]), (float)(320 - ututeki[kurikaesi][0]));
							//ラジアンの値を多少ランダムにする設定
							ututeki[kurikaesi][2] += ((GetRand(ututeki[kurikaesi][18] * 2)-ututeki[kurikaesi][18])/100)*(PI/180);
						if((ututeki[kurikaesi][0]-300)*(ututeki[kurikaesi][0] - 300)+ (ututeki[kurikaesi][1] - 240)*(ututeki[kurikaesi][1] - 240)>=ututeki[kurikaesi][13])
						{//遠かったら近づく設定
							ututeki[kurikaesi][0] += cos(ututeki[kurikaesi][2])*ututeki[kurikaesi][12];
							ututeki[kurikaesi][1] += sin(ututeki[kurikaesi][2])*ututeki[kurikaesi][12];
						}
						else if((ututeki[kurikaesi][0] - 300)*(ututeki[kurikaesi][0] - 300) + (ututeki[kurikaesi][1] - 240)*(ututeki[kurikaesi][1] - 240) <= ututeki[kurikaesi][14])
						{//近かったら遠ざかる設定
							ututeki[kurikaesi][0] -= cos(ututeki[kurikaesi][2])*ututeki[kurikaesi][12];
							ututeki[kurikaesi][1] -= sin(ututeki[kurikaesi][2])*ututeki[kurikaesi][12];
						}

						

					}
				}
				//撃つ敵の体当たりの攻撃の設定
				if (muteki >= 30) {
					for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
						if (ututeki[kurikaesi][5] >= 1) {
							if (ututeki[kurikaesi][0] - 18 < 325 && ututeki[kurikaesi][0] - 18 > 315 && ututeki[kurikaesi][1] - 18 < 245 && ututeki[kurikaesi][1] + 18 > 235) {
								//撃つ敵の左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= ututeki[kurikaesi][11]; muteki = 0;
							}
							else if (ututeki[kurikaesi][0] + 18 < 325 && ututeki[kurikaesi][0] + 18 > 315 && ututeki[kurikaesi][1] - 18 < 245 && ututeki[kurikaesi][1] + 18 > 235) {
								//撃つ敵の右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= ututeki[kurikaesi][11]; muteki = 0;
							}
							else if (ututeki[kurikaesi][0] - 18 < 325 && ututeki[kurikaesi][0] + 18 > 315 && ututeki[kurikaesi][1] - 18 < 245 && ututeki[kurikaesi][1] - 18 > 235) {
								//撃つ敵の上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= ututeki[kurikaesi][11]; muteki = 0;
							}
							else if (ututeki[kurikaesi][0] - 18 < 325 && ututeki[kurikaesi][0] + 18 > 315 && ututeki[kurikaesi][1] + 18 < 245 && ututeki[kurikaesi][1] + 18 > 235) {
								//撃つ敵の下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= ututeki[kurikaesi][11]; muteki = 0;
							}
							else if (ututeki[kurikaesi][0] - 18 < 325 && ututeki[kurikaesi][0] + 18 > 315 && ututeki[kurikaesi][1] - 18 < 245 && ututeki[kurikaesi][1] + 18 > 235) {
								//撃つ敵の壁が豆腐の内側に少しでも入っているかどうかを判定。
								tairyoku -= ututeki[kurikaesi][11]; muteki = 0;
							}
						}
					}
				}
				//ここから撃つ敵の弾の設定
				//ここから撃つ敵の弾を撃つ設定
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
					if (ututeki[kurikaesi][17] == 0&&ututeki[kurikaesi][5] > 0) {
						ututeki[kurikaesi][4] = 1;
						ututeki[kurikaesi][7] = ututeki[kurikaesi][0];
						ututeki[kurikaesi][8] = ututeki[kurikaesi][1];
						ututeki[kurikaesi][9] = ututeki[kurikaesi][2];
						ututeki[kurikaesi][17]++;
					}
					else if (ututeki[kurikaesi][3] > ututeki[kurikaesi][17]) { ututeki[kurikaesi][17]++;
					}
					else { ututeki[kurikaesi][17] = 0; ututeki[kurikaesi][4] = 0;}
					ututeki[kurikaesi][7] += cos(ututeki[kurikaesi][9])*ututeki[kurikaesi][16];
					ututeki[kurikaesi][8] += sin(ututeki[kurikaesi][9])*ututeki[kurikaesi][16];
				}
				
				//ここから撃つ敵の弾のあたり判定
				for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
						if (315 < ututeki[kurikaesi][7] && 325 > ututeki[kurikaesi][7]
							&& 235 < ututeki[kurikaesi][8] && 245 > ututeki[kurikaesi][8]
							&& ututeki[kurikaesi][4] == 1&&tairyoku>0) {
							ututeki[kurikaesi][4] = 0;
							tairyoku -= ututeki[kurikaesi][15];
							muteki = 0;
					}
				}
				//ここから撃ちまくる敵の設定
				//撃ちまくる敵の体当たりの攻撃の設定
				if (muteki >= 30) {
					for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
						if (utimakuruteki[kurikaesi][5] >= 1) {
							if (utimakuruteki[kurikaesi][0] - 18 < 325 && utimakuruteki[kurikaesi][0] - 18 > 315 && utimakuruteki[kurikaesi][1] - 18 < 245 && utimakuruteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= utimakuruteki[kurikaesi][11]; muteki = 0;
							}
							else if (utimakuruteki[kurikaesi][0] + 18 < 325 && utimakuruteki[kurikaesi][0] + 18 > 315 && utimakuruteki[kurikaesi][1] - 18 < 245 && utimakuruteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= utimakuruteki[kurikaesi][11]; muteki = 0;
							}
							else if (utimakuruteki[kurikaesi][0] - 18 < 325 && utimakuruteki[kurikaesi][0] + 18 > 315 && utimakuruteki[kurikaesi][1] - 18 < 245 && utimakuruteki[kurikaesi][1] - 18 > 235) {
								//ザコ敵の上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= utimakuruteki[kurikaesi][11]; muteki = 0;
							}
							else if (utimakuruteki[kurikaesi][0] - 18 < 325 && utimakuruteki[kurikaesi][0] + 18 > 315 && utimakuruteki[kurikaesi][1] + 18 < 245 && utimakuruteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= utimakuruteki[kurikaesi][11]; muteki = 0;
							}
							else if (utimakuruteki[kurikaesi][0] - 18 < 325 && utimakuruteki[kurikaesi][0] + 18 > 315 && utimakuruteki[kurikaesi][1] - 18 < 245 && utimakuruteki[kurikaesi][1] + 18 > 235) {
								//ザコ敵の内側に豆腐の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= utimakuruteki[kurikaesi][11]; muteki = 0;
							}
						}
					}
				}
				//ここから撃ちまくる敵の弾の設定
				//ここから撃ちまくる敵の弾を撃つ設定
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (utimakuruteki[kurikaesi][17] == 0 && utimakuruteki[kurikaesi][5] > 0) {
						utimakuruteki[kurikaesi][9] = atan2((float)(240 - utimakuruteki[kurikaesi][1]), (float)(320 - utimakuruteki[kurikaesi][0]));//ラジアンの値を出す魔法の計算式
						//ラジアンの値を多少ランダムにする設定
						utimakuruteki[kurikaesi][9] += ((GetRand(utimakuruteki[kurikaesi][28] * 2) - utimakuruteki[kurikaesi][28]) / 100)*(PI / 180);
						utimakuruteki[kurikaesi][4] = 1;
						utimakuruteki[kurikaesi][24] = 1;
						utimakuruteki[kurikaesi][25] = 1;
						utimakuruteki[kurikaesi][26] = 1;
						utimakuruteki[kurikaesi][27] = 1;
						utimakuruteki[kurikaesi][7] = utimakuruteki[kurikaesi][0];
						utimakuruteki[kurikaesi][8] = utimakuruteki[kurikaesi][1];
						utimakuruteki[kurikaesi][12] = utimakuruteki[kurikaesi][0];
						utimakuruteki[kurikaesi][13] = utimakuruteki[kurikaesi][1];
						utimakuruteki[kurikaesi][18] = utimakuruteki[kurikaesi][0];
						utimakuruteki[kurikaesi][19] = utimakuruteki[kurikaesi][1];
						utimakuruteki[kurikaesi][20] = utimakuruteki[kurikaesi][0];
						utimakuruteki[kurikaesi][21] = utimakuruteki[kurikaesi][1];
						utimakuruteki[kurikaesi][22] = utimakuruteki[kurikaesi][0];
						utimakuruteki[kurikaesi][23] = utimakuruteki[kurikaesi][1];
						utimakuruteki[kurikaesi][17]++;
					}
					else if (utimakuruteki[kurikaesi][3] > utimakuruteki[kurikaesi][17]) {
						utimakuruteki[kurikaesi][17]++;
					}
					else { utimakuruteki[kurikaesi][17] = 0;
					utimakuruteki[kurikaesi][4] = 0; 
					utimakuruteki[kurikaesi][24] = 0;
					utimakuruteki[kurikaesi][25] = 0;
					utimakuruteki[kurikaesi][26] = 0;
					utimakuruteki[kurikaesi][27] = 0;
					}
					utimakuruteki[kurikaesi][7] += cos(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(-2))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][8] += sin(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(-2))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][12] += cos(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(-1))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][13] += sin(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(-1))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][18] += cos(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(0))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][19] += sin(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(0))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][20] += cos(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(1))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][21] += sin(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(1))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][22] += cos(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(2))*utimakuruteki[kurikaesi][16];
					utimakuruteki[kurikaesi][23] += sin(utimakuruteki[kurikaesi][9] + utimakuruteki[kurikaesi][14] * (DX_PI / 180)*(2))*utimakuruteki[kurikaesi][16];
				}
				//ここから撃ちまくる敵の弾のあたり判定
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (315 < utimakuruteki[kurikaesi][7] && 325 > utimakuruteki[kurikaesi][7]
						&& 235 < utimakuruteki[kurikaesi][8] && 245 > utimakuruteki[kurikaesi][8]
						&& utimakuruteki[kurikaesi][4] == 1&&tairyoku>0) {
						utimakuruteki[kurikaesi][4] = 0;
						tairyoku -= utimakuruteki[kurikaesi][15];
						muteki = 0;
					}
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (315 < utimakuruteki[kurikaesi][12] && 325 > utimakuruteki[kurikaesi][12]
						&& 235 < utimakuruteki[kurikaesi][13] && 245 > utimakuruteki[kurikaesi][13]
						&& utimakuruteki[kurikaesi][24] == 1 && tairyoku>0) {
						utimakuruteki[kurikaesi][24] = 0;
						tairyoku -= utimakuruteki[kurikaesi][15];
						muteki = 0;
					}
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (315 < utimakuruteki[kurikaesi][18] && 325 > utimakuruteki[kurikaesi][18]
						&& 235 < utimakuruteki[kurikaesi][19] && 245 > utimakuruteki[kurikaesi][19]
						&& utimakuruteki[kurikaesi][25] == 1 && tairyoku>0) {
						utimakuruteki[kurikaesi][25] = 0;
						tairyoku -= utimakuruteki[kurikaesi][15];
						muteki = 0;
					}
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (315 < utimakuruteki[kurikaesi][20] && 325 > utimakuruteki[kurikaesi][20]
						&& 235 < utimakuruteki[kurikaesi][21] && 245 > utimakuruteki[kurikaesi][21]
						&& utimakuruteki[kurikaesi][26] == 1 && tairyoku>0) {
						utimakuruteki[kurikaesi][26] = 0;
						tairyoku -= utimakuruteki[kurikaesi][15];
						muteki = 0;
					}
				}
				for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
					if (315 < utimakuruteki[kurikaesi][22] && 325 > utimakuruteki[kurikaesi][22]
						&& 235 < utimakuruteki[kurikaesi][23] && 245 > utimakuruteki[kurikaesi][23]
						&& utimakuruteki[kurikaesi][27] == 1 && tairyoku>0) {
						utimakuruteki[kurikaesi][27] = 0;
						tairyoku -= utimakuruteki[kurikaesi][15];
						muteki = 0;
					}
				}
				//デカい敵の体当たりの攻撃の設定
				if (muteki >= 30) {
					for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
						if (dekaiteki[kurikaesi][5] >= 1) {
							if (dekaiteki[kurikaesi][0] - 36 < 325 && dekaiteki[kurikaesi][0] - 36 > 315 && dekaiteki[kurikaesi][1] - 36 < 245 && dekaiteki[kurikaesi][1] + 36 > 235) {
								//デカい敵の左側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= dekaiteki[kurikaesi][7]; muteki = 0;
							}
							else if (dekaiteki[kurikaesi][0] + 36 < 325 && dekaiteki[kurikaesi][0] + 36 > 315 && dekaiteki[kurikaesi][1] - 36 < 245 && dekaiteki[kurikaesi][1] + 36 > 235) {
								//デカい敵の右側の壁が豆腐の左右の壁に入っているときに豆腐の上下の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= dekaiteki[kurikaesi][7]; muteki = 0;
							}
							else if (dekaiteki[kurikaesi][0] - 36 < 325 && dekaiteki[kurikaesi][0] + 36 > 315 && dekaiteki[kurikaesi][1] - 36 < 245 && dekaiteki[kurikaesi][1] - 36 > 235) {
								//デカい敵の上側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= dekaiteki[kurikaesi][7]; muteki = 0;
							}
							else if (dekaiteki[kurikaesi][0] - 36 < 325 && dekaiteki[kurikaesi][0] + 36 > 315 && dekaiteki[kurikaesi][1] + 36 < 245 && dekaiteki[kurikaesi][1] + 36 > 235) {
								//デカい敵の下側の壁が豆腐の上下の壁に入っているときに豆腐の左右の壁の範囲に少しでも入っているかどうかを判定。
								tairyoku -= dekaiteki[kurikaesi][7]; muteki = 0;
							}
							else if (dekaiteki[kurikaesi][0] - 36 < 325 && dekaiteki[kurikaesi][0] + 36 > 315 && dekaiteki[kurikaesi][1] - 36 < 245 && dekaiteki[kurikaesi][1] + 36 > 235) {
								//デカい敵の内側に豆腐が入っているかどうかを判定。
								tairyoku -= dekaiteki[kurikaesi][7]; muteki = 0;
							}
						}
					}
				}
				
		
		SetBackgroundColor(200, 200, 200);
		//描画ゾーン
		ClearDrawScreen();
		//DrawGraph(0, 0, haikei, false);
		
		for (m = 0; m < n; m++)
		{
			DrawExtendGraph(kabeD[m][0][0], kabeD[m][1][0], (kabeD[m][0][1] - 1), (kabeD[m][1][1] - 1), bannou2, false);
		}
		for (kurikaesi = 0; kurikaesi < kuroikabenokazu; kurikaesi++)
		{
			DrawExtendGraph(kuroikabe[kurikaesi][0][0], kuroikabe[kurikaesi][1][0], (kuroikabe[kurikaesi][0][1] - 1), (kuroikabe[kurikaesi][1][1] - 1), kuroigazou, false);
		}
		for (i = 0; i < k; i++)
		{
			DrawExtendGraph(kabeL[i][0][0], kabeL[i][1][0], (kabeL[i][0][1] - 1), (kabeL[i][1][1] - 1), bannou, false);
		}
		for (p = 0; p < tanninokazu; p++)
		{
			DrawExtendGraph(tannikabe[p][0][0], tannikabe[p][1][0], (tannikabe[p][0][1] - 1), (tannikabe[p][1][1] - 1), tannigazou, false);
		}
		if (tairyoku > 0) {
			if ((muteki >= 5 && muteki < 10) || (muteki >= 15 && muteki < 20) ||
				(muteki >= 25 && muteki < 30)/* || (muteki >= 35 && muteki < 40) ||
				(muteki >= 45 && muteki < 50) || (muteki >= 55 && muteki < 60) ||
				(muteki >= 65 && muteki < 70) || (muteki >= 75 && muteki < 80) ||
				(muteki >= 85 && muteki < 90) || (muteki >= 95 && muteki < 100)*/) {
				DrawExtendGraph(315, 235, 324, 244, touhunaku, false);
			}
			else if (muteki >= 0 && muteki < 30) {}
			else if (mausuhidari >= 100) { DrawExtendGraph(315, 235, 324, 244, touhusuppai, false); }
			else if (mausuhidari >= 50) { DrawExtendGraph(315, 235, 324, 244, touhuhunbari, false); }
			else if (mausuhidari >= 1) { DrawExtendGraph(315, 235, 324, 244, touhumagao, false); }
			else if (mausuhidari == 0) { DrawExtendGraph(315, 235, 324, 244, touhu, false); }
		}

		//for (i = 0; i < k; i++) {
		//	DrawFormatString(kabeL[i][0][0], kabeL[i][1][0], GetColor(255, 0, 0), "(%d)", i);
		//}
		for (kurikaesi = 0; kurikaesi < tamakazu; kurikaesi++) {
			if (tama[kurikaesi][6] == 1) {
				DrawGraph(tama[kurikaesi][0] - 2, tama[kurikaesi][1] - 2, tamagazou, true);
			}
		}
		for (kurikaesi = 0; kurikaesi < 32; kurikaesi++) {
			if (tametama[kurikaesi][6] == 1) {
				DrawGraph(tametama[kurikaesi][0] - 2, tametama[kurikaesi][1] - 2, tamagazou, true);
			}
		}

		//DrawGraph(30, 30, huriwakeyarinaosi, true);
		//DrawGraph(30, 30, bosuteki, true);
		//回復アイテムの描写。
		for (kurikaesi = 0; kurikaesi < kaihukuaitemunokazu; kurikaesi++) {
			if (kaihukuaitemu[kurikaesi][3] == 1) {
				DrawGraph(kaihukuaitemu[kurikaesi][0] - 5, kaihukuaitemu[kurikaesi][1] - 5, kaihukuaitemugazou, false);
			}
		}
		//お金アイテムの描写。
		for (kurikaesi = 0; kurikaesi < okaneaitemunokazu; kurikaesi++) {
			if (okaneaitemu[kurikaesi][3] == 1) {
				DrawGraph(okaneaitemu[kurikaesi][0] - 5, okaneaitemu[kurikaesi][1] - 5, okaneaitemugazou, false);
			}
		}
		//ザコ敵の描写
		for (kurikaesi = 0; kurikaesi < zakotekinokazu; kurikaesi++) {
			if (zakoteki[kurikaesi][5] >= 1) {
				if (zakoteki[kurikaesi][5] <= 256 && zakoteki[kurikaesi][5] >= 1)
				{
					zakoteki[kurikaesi][6] = GetColor(zakoteki[kurikaesi][5] - 1, 0, 0); //黒から赤
				}
				else if (zakoteki[kurikaesi][5] <= 512 && zakoteki[kurikaesi][5] >= 257)
				{
					zakoteki[kurikaesi][6] = GetColor(255, zakoteki[kurikaesi][5] - 257, 0);//赤から黄
				}
				else if (zakoteki[kurikaesi][5] <= 768 && zakoteki[kurikaesi][5] >= 513)
				{
					zakoteki[kurikaesi][6] = GetColor(768 - zakoteki[kurikaesi][5], 255, 0);//黄から緑
				}
				else if (zakoteki[kurikaesi][5] <= 1024 && zakoteki[kurikaesi][5] >= 769)
				{
					zakoteki[kurikaesi][6] = GetColor(0, 255, zakoteki[kurikaesi][5] - 769);//緑から水
				}
				else if (zakoteki[kurikaesi][5] <= 1280 && zakoteki[kurikaesi][5] >= 1025)
				{
					zakoteki[kurikaesi][6] = GetColor(0, 1280 - zakoteki[kurikaesi][5], 255);//水から青
				}
				else if (zakoteki[kurikaesi][5] <= 1536 && zakoteki[kurikaesi][5] >= 1281)
				{
					zakoteki[kurikaesi][6] = GetColor(zakoteki[kurikaesi][5] - 1281, 0, 255);//青から紫
				}
				else if (zakoteki[kurikaesi][5] <= 1792 && zakoteki[kurikaesi][5] >= 1537)
				{
					zakoteki[kurikaesi][6] = GetColor(255, zakoteki[kurikaesi][5] - 1537, 255);//紫から白
				}
				else if (zakoteki[kurikaesi][5] >= 1793)
				{
					zakoteki[kurikaesi][6] = GetColor(255, 255, 255);//白
				}
				DrawCircle(zakoteki[kurikaesi][0], zakoteki[kurikaesi][1], 3, zakoteki[kurikaesi][6], TRUE);//円を描く。
				DrawGraph(zakoteki[kurikaesi][0] - 300, zakoteki[kurikaesi][1] - 300, zakotekinogazou, true);
				//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
					//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
			}
		}
		//撃つ敵の描写
		for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
			if (ututeki[kurikaesi][5] >= 1) {
				if (ututeki[kurikaesi][5] <= 256 && ututeki[kurikaesi][5] >= 1)
				{
					ututeki[kurikaesi][6] = GetColor(ututeki[kurikaesi][5] - 1, 0, 0); //黒から赤
				}
				else if (ututeki[kurikaesi][5] <= 512 && ututeki[kurikaesi][5] >= 257)
				{
					ututeki[kurikaesi][6] = GetColor(255, ututeki[kurikaesi][5] - 257, 0);//赤から黄
				}
				else if (ututeki[kurikaesi][5] <= 768 && ututeki[kurikaesi][5] >= 513)
				{
					ututeki[kurikaesi][6] = GetColor(768 - ututeki[kurikaesi][5], 255, 0);//黄から緑
				}
				else if (ututeki[kurikaesi][5] <= 1024 && ututeki[kurikaesi][5] >= 769)
				{
					ututeki[kurikaesi][6] = GetColor(0, 255, ututeki[kurikaesi][5] - 769);//緑から水
				}
				else if (ututeki[kurikaesi][5] <= 1280 && ututeki[kurikaesi][5] >= 1025)
				{
					ututeki[kurikaesi][6] = GetColor(0, 1280 - ututeki[kurikaesi][5], 255);//水から青
				}
				else if (ututeki[kurikaesi][5] <= 1536 && ututeki[kurikaesi][5] >= 1281)
				{
					ututeki[kurikaesi][6] = GetColor(ututeki[kurikaesi][5] - 1281, 0, 255);//青から紫
				}
				else if (ututeki[kurikaesi][5] <= 1792 && ututeki[kurikaesi][5] >= 1537)
				{
					ututeki[kurikaesi][6] = GetColor(255, ututeki[kurikaesi][5] - 1537, 255);//紫から白
				}
				else if (ututeki[kurikaesi][5] >= 1793)
				{
					ututeki[kurikaesi][6] = GetColor(255, 255, 255);//白
				}
				DrawCircle(ututeki[kurikaesi][0], ututeki[kurikaesi][1], 3, ututeki[kurikaesi][6], TRUE);//円を描く。
				DrawGraph(ututeki[kurikaesi][0] - 300, ututeki[kurikaesi][1] - 300, ututekinogazou, true);
				//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
				//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
			}
		}
		for (kurikaesi = 0; kurikaesi < ututekinokazu; kurikaesi++) {
			if (ututeki[kurikaesi][4] == 1) {
				DrawGraph(ututeki[kurikaesi][7] - 2, ututeki[kurikaesi][8] - 2, ututekinotamanogazou, true);
			}
		}
		//撃ちまくる敵の描写
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][5] >= 1) {
				if (utimakuruteki[kurikaesi][5] <= 256 && utimakuruteki[kurikaesi][5] >= 1)
				{
					utimakuruteki[kurikaesi][6] = GetColor(utimakuruteki[kurikaesi][5] - 1, 0, 0); //黒から赤
				}
				else if (utimakuruteki[kurikaesi][5] <= 512 && utimakuruteki[kurikaesi][5] >= 257)
				{
					utimakuruteki[kurikaesi][6] = GetColor(255, utimakuruteki[kurikaesi][5] - 257, 0);//赤から黄
				}
				else if (utimakuruteki[kurikaesi][5] <= 768 && utimakuruteki[kurikaesi][5] >= 513)
				{
					utimakuruteki[kurikaesi][6] = GetColor(768 - utimakuruteki[kurikaesi][5], 255, 0);//黄から緑
				}
				else if (utimakuruteki[kurikaesi][5] <= 1024 && utimakuruteki[kurikaesi][5] >= 769)
				{
					utimakuruteki[kurikaesi][6] = GetColor(0, 255, utimakuruteki[kurikaesi][5] - 769);//緑から水
				}
				else if (utimakuruteki[kurikaesi][5] <= 1280 && utimakuruteki[kurikaesi][5] >= 1025)
				{
					utimakuruteki[kurikaesi][6] = GetColor(0, 1280 - utimakuruteki[kurikaesi][5], 255);//水から青
				}
				else if (utimakuruteki[kurikaesi][5] <= 1536 && utimakuruteki[kurikaesi][5] >= 1281)
				{
					utimakuruteki[kurikaesi][6] = GetColor(utimakuruteki[kurikaesi][5] - 1281, 0, 255);//青から紫
				}
				else if (utimakuruteki[kurikaesi][5] <= 1792 && utimakuruteki[kurikaesi][5] >= 1537)
				{
					utimakuruteki[kurikaesi][6] = GetColor(255, utimakuruteki[kurikaesi][5] - 1537, 255);//紫から白
				}
				else if (utimakuruteki[kurikaesi][5] >= 1793)
				{
					utimakuruteki[kurikaesi][6] = GetColor(255, 255, 255);//白
				}
				DrawCircle(utimakuruteki[kurikaesi][0], utimakuruteki[kurikaesi][1], 3, utimakuruteki[kurikaesi][6], TRUE);//円を描く。
				DrawGraph(utimakuruteki[kurikaesi][0] - 300, utimakuruteki[kurikaesi][1] - 300, utimakurutekinogazou, true);
				//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
				//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！(←使わなくなった。)
			}
		}
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][4] == 1) {
				DrawGraph(utimakuruteki[kurikaesi][7] - 2, utimakuruteki[kurikaesi][8] - 2, aoigazou, true);
			}
		}
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][24] == 1) {
				DrawGraph(utimakuruteki[kurikaesi][12] - 2, utimakuruteki[kurikaesi][13] - 2, aoigazou, true);
			}
		}
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][25] == 1) {
				DrawGraph(utimakuruteki[kurikaesi][18] - 2, utimakuruteki[kurikaesi][19] - 2, aoigazou, true);
			}
		}
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][26] == 1) {
				DrawGraph(utimakuruteki[kurikaesi][20] - 2, utimakuruteki[kurikaesi][21] - 2, aoigazou, true);
			}
		}
		for (kurikaesi = 0; kurikaesi < utimakurutekinokazu; kurikaesi++) {
			if (utimakuruteki[kurikaesi][27] == 1) {
				DrawGraph(utimakuruteki[kurikaesi][22] - 2, utimakuruteki[kurikaesi][23] - 2, aoigazou, true);
			}
		}
		//デカい敵の描写
		for (kurikaesi = 0; kurikaesi < dekaitekinokazu; kurikaesi++) {
			if (dekaiteki[kurikaesi][5] >= 1) {
				if (dekaiteki[kurikaesi][5] <= 256 && dekaiteki[kurikaesi][5] >= 1)
				{
					dekaiteki[kurikaesi][6] = GetColor(dekaiteki[kurikaesi][5] - 1, 0, 0); //黒から赤
				}
				else if (dekaiteki[kurikaesi][5] <= 512 && dekaiteki[kurikaesi][5] >= 257)
				{
					dekaiteki[kurikaesi][6] = GetColor(255, dekaiteki[kurikaesi][5] - 257, 0);//赤から黄
				}
				else if (dekaiteki[kurikaesi][5] <= 768 && dekaiteki[kurikaesi][5] >= 513)
				{
					dekaiteki[kurikaesi][6] = GetColor(768 - dekaiteki[kurikaesi][5], 255, 0);//黄から緑
				}
				else if (dekaiteki[kurikaesi][5] <= 1024 && dekaiteki[kurikaesi][5] >= 769)
				{
					dekaiteki[kurikaesi][6] = GetColor(0, 255, dekaiteki[kurikaesi][5] - 769);//緑から水
				}
				else if (dekaiteki[kurikaesi][5] <= 1280 && dekaiteki[kurikaesi][5] >= 1025)
				{
					dekaiteki[kurikaesi][6] = GetColor(0, 1280 - dekaiteki[kurikaesi][5], 255);//水から青
				}
				else if (dekaiteki[kurikaesi][5] <= 1536 && dekaiteki[kurikaesi][5] >= 1281)
				{
					dekaiteki[kurikaesi][6] = GetColor(dekaiteki[kurikaesi][5] - 1281, 0, 255);//青から紫
				}
				else if (dekaiteki[kurikaesi][5] <= 1792 && dekaiteki[kurikaesi][5] >= 1537)
				{
					dekaiteki[kurikaesi][6] = GetColor(255, dekaiteki[kurikaesi][5] - 1537, 255);//紫から白
				}
				else if (dekaiteki[kurikaesi][5] >= 1793)
				{
					dekaiteki[kurikaesi][6] = GetColor(255, 255, 255);//白
				}
				DrawCircle(dekaiteki[kurikaesi][0], dekaiteki[kurikaesi][1], 3, dekaiteki[kurikaesi][6], TRUE);//円を描く。
				DrawGraph(dekaiteki[kurikaesi][0] - 300, dekaiteki[kurikaesi][1] - 300, dekaitekinogazou, true);
				//DrawFormatString(zakoteki[kurikaesi][0]-5, zakoteki[kurikaesi][1]-8, GetColor(255, 255, 255),
				//"%3.0f",zakoteki[kurikaesi][5]);//3.0fは、整数3桁、小数0桁のことを意味している。ここでは体力4桁以上は無理になってる！
			}
		}
		//ステージ上のメモの設定
		if (genzainosutezi == 1) {
			DrawFormatString(memo[0][0], memo[0][1], GetColor(0, 0, 0), "<<移動ボタン>>\n     W\n     ↑\n  A←  →D     右へ進む  →  →  →  →  →  →\n     ↓\n     S");
			DrawFormatString(memo[1][0], memo[1][1], GetColor(0, 0, 0), "マウスカーソルで敵を狙う     右へ進む  →  →  →  →  →  →\n左クリック長押しで溜める\n右下の黄色いゲージが溜まったら離す\n溜めは2段階ある\n溜めない方がダメージ効率がよい");
			DrawFormatString(memo[2][0], memo[2][1], GetColor(0, 0, 0), "緑色の壁は通り抜けられない\n紫の壁は触れるとダメージを受ける\n黒い壁に触れると即死\nENTERを押すとメニュー画面に戻る\n(誤って押さないように注意)");
			DrawFormatString(memo[3][0], memo[3][1], GetColor(0, 0, 0), "敵に弾を当てて倒そう\n敵を倒すと$が手に入る\n敵の本体や敵の弾にぶつかるとダメージ");
			DrawFormatString(memo[4][0], memo[4][1], GetColor(0, 0, 0), "ハート体力回復\n$お金が手に入る");
			DrawFormatString(memo[5][0], memo[5][1], GetColor(0, 0, 0), "左上の単位必要数まで単位を集めるとステージクリア\n次のステージに進めるようになる\n※クリアした後に死んでもクリアしたことになります。");
		}
		if (genzainosutezi == 8) {
			DrawFormatString(memo[0][0], memo[0][1], GetColor(0, 0, 0), "最後のステージです。\n");
			DrawFormatString(memo[1][0], memo[1][1], GetColor(0, 0, 0), "最大までステータスを上昇させないとクリア出来ないと思います...");
			DrawFormatString(memo[2][0], memo[2][1], GetColor(0, 0, 0), "もはや無理ゲー");
			DrawFormatString(memo[3][0], memo[3][1], GetColor(0, 0, 0), "留年");
			DrawFormatString(memo[4][0], memo[4][1], GetColor(0, 0, 0), "回復アイテムが重要");
			DrawFormatString(memo[5][0], memo[5][1], GetColor(0, 0, 0), "単位がほしい");
		}
		/*
		if (CheckHitKey(KEY_INPUT_Z) == 1)
		for (i = 0; i < k; i++) {
			DrawFormatString(0, i * 20 + 20, GetColor(255, 255,255), "%d,X(%d～%d)Y(%d～%d)", i, kabeL[i][0][0], kabeL[i][0][1],
				kabeL[i][1][0], kabeL[i][1][1]);
		}
		if (CheckHitKey(KEY_INPUT_X) == 1)
			for (m = 0; m < 20; m++) {
				DrawFormatString(0, m * 20 + 20, GetColor(255, 0, 0), "%d,X(%d～%d)Y(%d～%d)", m, kabeD[m][0][0], kabeD[m][0][1],
					kabeD[m][1][0], kabeD[m][1][1]);
			}
			*/
		//DrawFormatString(290, 210, GetColor(255, 0, 0), "(X;%d,Y;%d,)", -kabeL[0][0][0] + 290, -kabeL[0][1][0] + 210);
		if (tannihituyousuu>genzainotanninokazu) {//単位の必要数を表示
			DrawFormatString(0, 0, GetColor(255, 255, 255), "単位;%d/%d,", genzainotanninokazu, tannihituyousuu);
		}
		else if (tannihituyousuu <= tannihituyousuu) { 
			DrawFormatString(0, 0, GetColor(255, 255, 255), "単位;%d/%d,\nステージクリア!!\nENTERでメニュー画面へ戻る", genzainotanninokazu, tannihituyousuu);
			if (genzainosutezi >= sutezinosaidaiti) { sutezinosaidaiti++; }
			if (sutezinosaidaiti >= 9) { sutezinosaidaiti = 8; }
		}
		
			DrawFormatString(100, 0, GetColor(255, 255, 255), "お金;%d",okane);
		
		/*DrawFormatString(100, 100, GetColor(255, 255, 255), "X(%d)Y(%d),距離二乗%d,kaiten%d,左%d中%d右%d", mausux, mausuy,
			((mausux - 320)*(mausux - 320) + (mausuy - 240)*(mausuy - 240)),
			mausukaiten,mausuhidari,mausumannnaka,mausumigi);//*/
			//DrawFormatString(100, 100, GetColor(255, 255, 255), "%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f,\n%f", ututeki[0][0], ututeki[0][1], ututeki[0][2], ututeki[0][3], ututeki[0][4], ututeki[0][5], ututeki[0][6], ututeki[0][7], ututeki[0][8], ututeki[0][9], ututeki[0][10], ututeki[0][11], ututeki[0][12] );
			
		DrawBox(640-tairyokusaidaiti-2, 470, 640, 480, GetColor(0,0,0), TRUE);    // 四角形を描画 
		if (tairyoku >= 1) {
			DrawBox(640 - tairyoku - 1, 471, 639, 479, GetColor(0, 255, 0), TRUE);
		}
		DrawBox(588, 461, 640, 471, (0, 0, 0), TRUE);    // 四角形を描画
		if(mausuhidari<=49&&mausuhidari>=0){ DrawBox(639-mausuhidari, 462, 639, 470, GetColor(255, 255, 0), TRUE); }
		if (mausuhidari <= 99 && mausuhidari >= 50) { DrawBox(639 - mausuhidari+50, 462, 639, 470, GetColor(255, 100, 0), TRUE); }
		if (mausuhidari >= 100) { DrawBox(589, 462, 639, 470, GetColor(255, 0, 0), TRUE); }
		if (tairyoku <= 0) {
			DrawFormatString(220, 225, GetColor(0, 0, 0), "ENTERでメニュー画面に戻る");
		}
		//DrawFormatString(x, (y - 10), GetColor(255, 255, 255), "(%d,%d)", x, y);
		ScreenFlip();
		//描画ゾーン,画面の大きさは、640*480
	}
	
	}

	DxLib_End();
	return 0;
}


