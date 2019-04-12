#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MethordHuClass.h"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <QDateTime>
#include <time.h>
using namespace std;
vector <string> hupai;

const char* huPaiFan[] = {"1大四喜","2大三元","3绿一色","4九宝莲灯","5四个杠","6连七对","7十三幺","8清幺九","9小四喜",
                          "10小三元","11字一色","12四暗刻","13一色双龙会","14一色四同顺","15一色四节高", "16一色四步高",
                          "17三个杠", "18混幺九","19七对","20七星不靠","21全双刻","22清一色","23一色三同顺","24一色三节高",
                          "25全大","26全中","27全小","28清龙","29三色双龙会","30一色三步高","31全带五","32三同刻","33三暗刻",
                          "34全不靠", "35组合龙","36大于五","37小于五","38三风刻","39花龙","40推不倒","41三色三同顺","42三色三节高",
                          "43无番和","44妙手回春","45海底捞月","46杠上开花","47抢杠和","48碰碰和","49混一色","50三色三步高","51五门齐",
                          "52全求人","53双暗杠","54双箭刻","55全带幺","56不求人","57双明杠","58和绝张","59箭刻","60圈风刻","61门风刻",
                          "62门前清","63平和","64双同刻","65四归一*1","66四归一*2","67双暗刻","68暗杠","69断幺","70一般高*1","71一般高*2",
                          "72喜相逢*1","73喜相逢*2","74连六","75老少副*1","76老少副*2","77幺九刻*1","78幺九刻*2","79幺九刻*4",
                          "80明杠","81缺一门","82无字","83边张","84坎张","85单调将","86自摸","87花牌*1","88花牌*2","89花牌*4","90花牌*8"};


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->textEdit_2->clear();
    ui->textEdit_2->setFontPointSize(16);

    QString anGangPai = ui->lineEdit->text();
    QStringList anGangList = anGangPai.split(",");
    if (anGangPai.size() != 0 && anGangList.count() % 4 != 0)
    {
        ui->textEdit_2->setText("暗杠输入错误，请检测。。。。");
        return;
    }
    vector <int> anGangVec;
    for (int ii = 0; ii < anGangList.count() && anGangPai.size() > 0; ++ii)
    {
        if (ii == 0)
            anGangVec.push_back(anGangList.at(ii).toInt());
        if (ii == 4)
            anGangVec.push_back(anGangList.at(ii).toInt());
        if (ii == 8)
            anGangVec.push_back(anGangList.at(ii).toInt());
        if (ii == 12)
            anGangVec.push_back(anGangList.at(ii).toInt());
    }

    QString minGangPai = ui->lineEdit_2->text();
    QStringList minGangList = minGangPai.split(",");
    if (minGangPai.size() != 0 && minGangList.count() % 4 != 0)
    {
        ui->textEdit_2->setText("明杠输入错误，请检测。。。。");
        return;
    }
    vector <int> minGangVec;
    for (int ii = 0; ii < minGangList.count() && minGangPai.size() > 0; ++ii)
    {
        if (ii == 0)
            minGangVec.push_back(minGangList.at(ii).toInt());
        if (ii == 4)
            minGangVec.push_back(minGangList.at(ii).toInt());
        if (ii == 8)
            minGangVec.push_back(minGangList.at(ii).toInt());
        if (ii == 12)
            minGangVec.push_back(minGangList.at(ii).toInt());
    }

    QString chiPai = ui->lineEdit_3->text();
    QStringList chiPaiList = chiPai.split(",");
    if (chiPai.size()!= 0 && chiPaiList.count() % 3 != 0)
    {
        ui->textEdit_2->setText("吃牌输入错误，请检测。。。。...............");
        return;
    }
    vector <int> chiPaiVec;
    for (int ii = 0; ii < chiPaiList.count() - 2; ii += 3)
    {
        //cout << chiPaiList.at(ii).toStdString() << endl;
        //cout << chiPaiList.at(ii + 1).toStdString() << endl;
        //cout << chiPaiList.at(ii + 2).toStdString() << endl;
        if (chiPaiList.at(ii).toInt() + 1 == chiPaiList.at(ii + 1).toInt() && (chiPaiList.at(ii).toInt() + 2) == chiPaiList.at(ii + 2).toInt())
            chiPaiVec.push_back(chiPaiList.at(ii).toInt());
        else
        {
            ui->textEdit_2->setText("吃牌输入错误，请检测。。。。");
            return;
        }
    }

    QString pengPai = ui->lineEdit_4->text();
    QStringList pengList = pengPai.split(",");
    if (pengPai.size() != 0 && pengList.count() % 3 != 0)
    {
        ui->textEdit_2->setText("碰牌输入错误，请检测。。。。");
        return;
    }
    vector <int> pengPaiVec;
    for (int ii = 0; ii < pengList.count() && pengPai.size() > 0; ++ii)
    {
        if (ii == 0)
            pengPaiVec.push_back(pengList.at(ii).toInt());
        if (ii == 3)
            pengPaiVec.push_back(pengList.at(ii).toInt());
        if (ii == 6)
            pengPaiVec.push_back(pengList.at(ii).toInt());
        if (ii == 9)
            pengPaiVec.push_back(pengList.at(ii).toInt());
    }

    vector <int> handCard;
    handCard.clear();
    QString shouPai = ui->lineEdit_5->text();
    cout << shouPai.toStdString() << endl;
    QStringList strVec = shouPai.split(",");
    for (int i = 0; i < strVec.count(); ++i)
    {
        handCard.push_back(strVec.at(i).toInt());
    }

    vector <int> huDePai;
    huDePai.clear();
    QString huPai = ui->lineEdit_6->text();
    cout << huPai.toStdString() << endl;
    QStringList huDePaiVec = huPai.split(",");
    for (int i = 0; i < huDePaiVec.size(); ++i)
    {
        huDePai.push_back(huDePaiVec.at(i).toInt());
        if(huDePai.size() != 1){
            ui->textEdit_2->setText("胡的牌输入错误，请检测。。。。");
            return;
        }
    }
    cout<<"__________1-------------"<<endl;

    int Cards[49];
    memset(Cards,0,sizeof(Cards));

    for(vector <int>::iterator it = handCard.begin();it != handCard.end();it++){
        Cards[*it-1]++;
    }
    vector<char> cardting;

    std::list<CMjCardPile> p_desk;

    for(vector <int>::iterator it = anGangVec.begin();it!= anGangVec.end();it++){
        CMjCardPile p_temp;
		p_temp.SetCardPile(*it, SPECIAL_TYPE_ANGANG);
        p_desk.push_back(p_temp);
    }

    for(vector <int>::iterator it = minGangVec.begin();it!= minGangVec.end();it++){
        CMjCardPile p_temp;
		p_temp.SetCardPile(*it, SPECIAL_TYPE_MINGGANG);
        p_desk.push_back(p_temp);
    }

    for(vector <int>::iterator it = pengPaiVec.begin();it!= pengPaiVec.end();it++){
        CMjCardPile p_temp;
		p_temp.SetCardPile(*it, SPECIAL_TYPE_PENG);
        p_desk.push_back(p_temp);
    }

    for(vector <int>::iterator it = chiPaiVec.begin();it!= chiPaiVec.end();it++){
        CMjCardPile p_temp;
		p_temp.SetCardPile(*it,SPECIAL_TYPE_SHUN);
        p_desk.push_back(p_temp);
    }

    cout<<"--2"<<endl;

    if(!MethordHuClass::getInstance()->CheckTing(Cards,p_desk,cardting))
    {
        ui->textEdit_2->setText("手牌不能胡牌，请检测。。。。");
        return;
    }
    cout<<cardting.size()<<endl;

    /*
     MethordHuClass tmp;
    sort(handCard.begin(), handCard.end());
    tmp.sethandCard(handCard, anGangVec, minGangVec, chiPaiVec, pengPaiVec);
    if (!tmp.IsCanhu(handCard))
    {
        ui->textEdit_2->setText("手牌不能胡牌，请检测。。。。");
        return;
    }
    */

    unsigned int result_fan[3];
    int result_fannum = 0;
    memset(result_fan,0,sizeof(result_fan));

    Cards[huDePai[0]-1] += 1;

    MethordHuClass::getInstance()->GetFans(Cards,p_desk,result_fan,result_fannum,0,false,huDePai[0],0,(cardting.size() == 1),true,0);
    printf("result_fannum = %d",result_fannum);
    QString strAll;
    strAll.clear();
    strAll += anGangPai + "," + minGangPai + "," + chiPai + "," + pengPai + "," + shouPai +"," + huPai + "\n";

    for(int i = 0;i != 3;i++){
        char cArrayValue[100] = { 0 };
        sprintf(cArrayValue, "result_fan[i] = %d\n", result_fan[i]);
        cout<<cArrayValue<<endl;
        for(int j = 0;j!=32;j++){
            if(i == 2 && j >25)
                continue;
            if((result_fan[i] & (1<< j)) == (1<< j))
            {
                strAll += huPaiFan[i*32+j];
                strAll += "\n";
            }
        }
    }

    char cArrayValue[30] = { 0 };
    sprintf(cArrayValue, "共计%d番", result_fannum);

    strAll += cArrayValue;

    /*
    hupai.clear();
    hupai = tmp.getHuPai();
    for (size_t ii = 0; ii < hupai.size(); ++ii)
    {
        strAll += hupai[ii].c_str();
        strAll += "\n";
    }
    */
    ui->textEdit_2->setText(strAll);
}
