#include <iostream>
#include <malloc.h>
#include <string.h>
#include <fstream>
#define PassWord "admin123"
using namespace std;

struct Staff_Info
{
    int num; //编号
    char name[10];
    char sex[4];
    char birthday[20];
    int age;
    char phoneNumber[11];
    char department[20];         //所属部门
    char professional_title[20]; //职称
    int wage_scale;              //工资级别（如1，2，3，4）
};

typedef struct StaffNode
{
    struct Staff_Info Staffdata;
    struct StaffNode *next;
    int Size;
} Node, *LinkList;

void login();
void visitorBackground();
void adminBackground();
void printStaffInfo(Staff_Info *p);
void Init(LinkList &head);
void showMenu();
void showPart_Menu();
void exitSystem();
void addStaff(LinkList &head);
void showStaffList(LinkList head);
bool secondPassword();
void delStaffByName(LinkList &head);
LinkList isExist(LinkList head);
void findStaffByName(LinkList head);
void updateStaffByName(LinkList &head);
void sortStaff(LinkList &head);
void sortStaffByNum(LinkList &head);
void sortStaffByWage(LinkList &head);
void clearStaff(LinkList &head);
void savefile(LinkList head);
void readfile(LinkList &head);

void login()
{
    cout << "欢迎进入职工档案管理系统!" << endl;
    cout << "请选择你要登录的方式：" << endl;
    cout << "1----->游客登录" << endl;
    cout << "2----->管理员登录" << endl;
    cout << "0----->退出系统" << endl;
    int select;
    cin >> select;
    while (1)
    {
        switch (select)
        {
        case 1:
            visitorBackground();
            return;
        case 2:
            adminBackground();
            return;
        case 0:
            cout << "正在退出系统，请稍后..." << endl;
            system("pause");
            exit(0);
        default:
            cout << "输入有误，请重新输入！" << endl;
            break;
        }
        cin >> select;
    }
}

void visitorBackground()
{
    system("cls");
    LinkList sta;
    readfile(sta);
    int select = 0;
    while (1)
    {
        showPart_Menu();
        cin >> select;
        switch (select)
        {
        case 1:
            showStaffList(sta);
            break;
        case 2:
            findStaffByName(sta);
            break;
        case 0:
            exitSystem();
            break;
        }
    }
    free(sta); //释放头节点
}

void adminBackground()
{
    char root[20];
    char password[20];

    char _root[20];
    char _password[20];

    ifstream ifs;
    ifs.open("Administrator_Info.txt", ios::in);

    if (!ifs.is_open()) //存储管理员的文件夹未建立
    {
        cout << "管理员信息库未建立!请建立后再试。" << endl;
        cout << "正在退出系统..." << endl;
        system("pause");
        exit(0);
    }

    while (1)
    {
        int flag=0;
        cout << "请输入管理员账号：" << endl;
        cin >> root;
        cout << "请输入管理员密码：" << endl;
        cin >> password;
        while (ifs >> _root >> _password)
        {
            if (!strcmp(_root, root) && !strcmp(_password, password)) //账号和密码同时正确
            {
                flag=1;
                cout << "登陆成功！" << endl;
                system("pause");
                break;
            }
        }
        cout << "输入的账号或密码有误，请重新输入!" << endl;
        ifs.clear();//清除流状态标志
        ifs.seekg(0,ios::beg);//流指针重新定位到文件开头
        if (flag==1) break;
    }

    system("cls");
    LinkList sta;
    readfile(sta);
    int select = 0;
    while (1)
    {
        showMenu();
        cin >> select;
        switch (select)
        {
        case 1:
            addStaff(sta);
            break;
        case 2:
            showStaffList(sta);
            break;
        case 3:
            delStaffByName(sta);
            break;
        case 4:
            findStaffByName(sta);
            break;
        case 5:
            updateStaffByName(sta);
            break;
        case 6:
            sortStaff(sta);
            break;
        case 8:
            clearStaff(sta);
            break;
        case 0:
            exitSystem();
            break;
        }
    }
    free(sta); //释放头节点
}

void showMenu()
{
    cout << "\t\t***************职工档案管理系统************" << endl;
    cout << "\t\t\t\t1、录入职工信息" << endl;
    cout << "\t\t\t\t2、显示职工信息" << endl;
    cout << "\t\t\t\t3、删除职工信息" << endl;
    cout << "\t\t\t\t4、查找职工信息" << endl;
    cout << "\t\t\t\t5、修改职工信息" << endl;
    cout << "\t\t\t\t6、排序" << endl;
    cout << "\t\t\t\t7、清空全部职工" << endl;
    cout << "\t\t\t\t0、退出系统\n"
         << endl;
    cout << "\t\t------> 请选择操作项并输入操作项编号：";
}

void showPart_Menu()
{
    cout << "\t\t***************职工档案管理系统************" << endl;
    cout << "\t\t\t\t1、显示职工信息" << endl;
    cout << "\t\t\t\t2、查找职工信息" << endl;
    cout << "\t\t\t\t0、退出系统\n"
         << endl;
    cout << "\t\t------> 请选择操作项并输入操作项编号：";
}

void exitSystem()
{
    cout << "欢迎下次使用，再见！" << endl;
    system("pause");
    exit(0);
}

void Init(LinkList &head) //初始化链表
{
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->Size = 0;
}

void printStaffInfo(Staff_Info *cur)
{
    cout << "编号：" << cur->num;
    cout << "  姓名：" << cur->name;
    cout << "  性别：" << cur->sex;
    cout << "  生日：" << cur->birthday;
    cout << "  年龄：" << cur->age;
    cout << "  电话：" << cur->phoneNumber;
    cout << "  所属部门：" << cur->department;
    cout << "  职称：" << cur->professional_title;
    cout << "  工资级别：" << cur->wage_scale << endl;
} //该输出用于屏幕输出

void addStaff(LinkList &head)
{
    LinkList t = head;
    cout << "请输入你要添加的职工数量：";
    int count = 0;
    cin >> count;
    while (t->next != NULL)
    {
        t = t->next;
    } //开始赋值时，使t永远指向链表的最后一个节点

    ofstream ofs;
    ofs.open("staff.txt", ios::out | ios::app); //以追加方式写入文件

    if (!ofs.is_open())
    {
        cout << "文件打开失败！" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        LinkList s = (Node *)malloc(sizeof(Node));

        cout << "请输入职工的编号：";
        cin >> s->Staffdata.num;
        cout << "请输入职工的姓名：";
        cin >> s->Staffdata.name;
        cout << "请输入职工的性别：";
        cin >> s->Staffdata.sex;
        cout << "请输入职工的生日（如1999年03月14日）：";
        cin >> s->Staffdata.birthday;
        cout << "请输入职工的年龄：";
        cin >> s->Staffdata.age;
        cout << "请输入职工的电话：";
        cin >> s->Staffdata.phoneNumber;
        cout << "请输入职工的电话所属部门：";
        cin >> s->Staffdata.department;
        cout << "请输入职工的职称：";
        cin >> s->Staffdata.professional_title;
        cout << "请输入职工的工资级别：";
        cin >> s->Staffdata.wage_scale;

        ofs << s->Staffdata.num << " "
            << s->Staffdata.name << " "
            << s->Staffdata.sex << " "
            << s->Staffdata.birthday << " "
            << s->Staffdata.age << " "
            << s->Staffdata.phoneNumber << " "
            << s->Staffdata.department << " "
            << s->Staffdata.professional_title << " "
            << s->Staffdata.wage_scale << endl; //以空格为分界符，分别读取

        t->next = s;
        t = s;
        head->Size++;
        cout << "录入完成！" << endl;
    }
    t->next = NULL;
    ofs.close();
    cout << "职工信息录入完成，本次共录入" << count << "个职工信息,共有" << head->Size << "个职工信息." << endl;
    system("pause");
    system("cls");
}

void showStaffList(LinkList head)
{
    system("cls");
    if (head->Size == 0)
    {
        cout << "没有职工信息！" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "已显示" << head->Size << "条职工信息" << endl;
    cout << "↓" << endl;
    LinkList p = head->next;
    int count = 0; //用于实现10行10行的输出，按任意键显示下一页
    int page = 0;  //当前页数
    int sumpage;   //总共页数
    if ((head->Size) % 10 == 0)
    {
        sumpage = head->Size / 10;
    }
    else if ((head->Size) % 10 != 0)
    {
        sumpage = (head->Size / 10) + 1;
    }
    for (int i = 0; i < head->Size; i++)
    {
        printStaffInfo(&(p->Staffdata));
        p = p->next;
        count++;
        if (count % 10 == 0)
        {
            page++;
            cout << "页数：" << page << "/" << sumpage << endl;
            system("pause");
            system("cls");
        }
    }
    if (head->Size % 10 != 0)
    {
        cout << "页数：" << page + 1 << "/" << sumpage << endl;
        system("pause");
        system("cls");
    }
}

LinkList isExist(LinkList head, char *name)
{
    LinkList p = head->next;
    LinkList pre = head;
    for (int i = 0; i < head->Size && strcmp(p->Staffdata.name, name); i++) //比较两字符串，不相等时进行循环
    {
        p = p->next;
        pre = pre->next;
    }
    if (p == NULL) //找不到
    {
        return NULL;
    }
    return pre; //找到返回前继节点
}

bool secondPassword() //输入密码
{
    cout << "请输入密码：" << endl;
    char password[20];
    int times = 4;
    cin >> password;
    while (strcmp(password, PassWord))
    {
        if (times == 0)
        {
            cout << "密码输错已达上限，正在退出该选项..." << endl;
            system("pause");
            system("cls");
            return false;
        }
        cout << "密码错误，请再次输入！你还有" << times << "次输入机会。" << endl;
        times--;
        cin >> password;
    }
    return true;
}

void delStaffByName(LinkList &head)
{
    if (!secondPassword()) //密码输入失败返回
        return;
    cout << "请输入要删除的职工的姓名：";
    char name[20];
    cin >> name;
    LinkList pos = isExist(head, name); //判断职工在链表中是否存在，若存在并返回它的前继指针，不存在则返回NULL
    if (pos == NULL)
    {
        cout << "该职工不存在！" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        LinkList d = pos->next; //d为待删除节点
        pos->next = pos->next->next;
        free(d);
        cout << "删除完成！" << endl;
        head->Size--;
        savefile(head); //删除后重新保存文件
        system("pause");
        system("cls");
    }
}

void findStaffByName(LinkList head) //查找符合该名字的所有职工
{
    cout << "请输入要查找的职工的姓名：";
    char name[20];
    cin >> name;
    int count = 0;

    LinkList p = head->next;
    while (p != NULL)
    {
        if (!strcmp(p->Staffdata.name, name)) //姓名匹配时，条件为真
        {
            printStaffInfo(&(p->Staffdata));
            count++;
        }
        p = p->next; //不匹配指针后移
    }
    if (count == 0)
    {
        cout << "姓名为" << name << "的职工不存在！" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "共显示" << count << "个姓名为" << name << "的职工信息！" << endl;
    system("pause");
    system("cls");
}

void sortStaffByNum(LinkList &head)
{
    cout << "请选择按编号排序的顺序（按0表示从小到大，按1表示从大到小）：";
    int select;

    while (1)
    {
        cin >> select;
        if (select == 0)
        {
            for (LinkList p = head->next; p != NULL; p = p->next)
            {
                for (LinkList q = head->next; q->next != NULL; q = q->next)
                {
                    if (q->Staffdata.num > q->next->Staffdata.num)
                    {
                        struct Staff_Info tempInfo = q->Staffdata;
                        q->Staffdata = q->next->Staffdata;
                        q->next->Staffdata = tempInfo;
                    }
                }
            }
            savefile(head);
            cout << "排序完成！" << endl;
            system("pause");
            system("cls");
            return;
        }
        if (select == 1)
        {
            for (LinkList p = head->next; p != NULL; p = p->next)
            {
                for (LinkList q = head->next; q->next != NULL; q = q->next)
                {
                    if (q->Staffdata.num < q->next->Staffdata.num)
                    {
                        struct Staff_Info tempInfo = q->Staffdata;
                        q->Staffdata = q->next->Staffdata;
                        q->next->Staffdata = tempInfo;
                    }
                }
            }
            savefile(head);
            cout << "排序完成！" << endl;
            system("pause");
            system("cls");
            return;
        }
        cout << "输入有误，请重新输入！" << endl;
    }
}

void sortStaffByWage(LinkList &head)
{
    cout << "请选择按工资级别排序的顺序（按0表示从小到大，按1表示从大到小）：";
    int select;
    while (1)
    {
        cin >> select;
        if (select == 0)
        {
            for (LinkList p = head->next; p != NULL; p = p->next)
            {
                for (LinkList q = head->next; q->next != NULL; q = q->next)
                {
                    if (q->Staffdata.wage_scale > q->next->Staffdata.wage_scale)
                    {
                        struct Staff_Info tempInfo = q->Staffdata;
                        q->Staffdata = q->next->Staffdata;
                        q->next->Staffdata = tempInfo;
                    }
                }
            }
            savefile(head);
            cout << "排序完成！" << endl;
            system("pause");
            system("cls");
            return;
        }
        if (select == 1)
        {
            for (LinkList p = head->next; p != NULL; p = p->next)
            {
                for (LinkList q = head->next; q->next != NULL; q = q->next)
                {
                    if (q->Staffdata.wage_scale < q->next->Staffdata.wage_scale)
                    {
                        struct Staff_Info tempInfo = q->Staffdata;
                        q->Staffdata = q->next->Staffdata;
                        q->next->Staffdata = tempInfo;
                    }
                }
            }
            savefile(head);
            cout << "排序完成！" << endl;
            system("pause");
            system("cls");
            return;
        }
        cout << "输入有误，请重新输入！" << endl;
    }
}

void sortStaff(LinkList &head)
{
    cout << "请选择排序的方式：" << endl;
    cout << "1.按编号排序" << endl;
    cout << "2.按工资级别排序" << endl;
    int select;
    while (1)
    {
        cin >> select;
        switch (select)
        {
        case 1:
            sortStaffByNum(head);
            return;
        case 2:
            sortStaffByWage(head);
            return;
        default:
            cout << "输入有误，请重新输入！" << endl;
            break;
        }
    }
}
void updateStaffByName(LinkList &head)
{
    if (!secondPassword()) //密码输入失败返回
        return;
    cout << "请输入你要修改的职工的姓名：";
    char name[20];
    cin >> name;
    LinkList pos = isExist(head, name);
    if (pos == NULL)
    {
        cout << "该职工不存在！" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "请输入职工的编号：";
        cin >> pos->next->Staffdata.num;
        cout << "请输入职工的姓名：";
        cin >> pos->next->Staffdata.name;
        cout << "请输入职工的性别：";
        cin >> pos->next->Staffdata.sex;
        cout << "请输入职工的生日（如1999年03月14日）：";
        cin >> pos->next->Staffdata.birthday;
        cout << "请输入职工的年龄：";
        cin >> pos->next->Staffdata.age;
        cout << "请输入职工的电话：";
        cin >> pos->next->Staffdata.phoneNumber;
        cout << "请输入职工的电话所属部门：";
        cin >> pos->next->Staffdata.department;
        cout << "请输入职工的职称：";
        cin >> pos->next->Staffdata.professional_title;
        cout << "请输入职工的工资级别：";
        cin >> pos->next->Staffdata.wage_scale;
        savefile(head);
        system("pause");
        system("cls");
    }
}

void clearStaff(LinkList &head) //不释放头节点，只释放后继的所有节点
{
    if (!secondPassword()) //密码输入失败返回
        return;
    LinkList p = head->next;
    LinkList pre = p;
    while (p != NULL)
    {
        p = p->next;
        free(pre); //释放
        pre = p;
    }
    free(pre);
    head->Size = 0;
    head->next = NULL;
    savefile(head);
    cout << "职工信息已清空！" << endl;
    system("pause");
    system("cls");
}

//保存文件部分
void savefile(LinkList head)
{
    ofstream ofs;
    ofs.open("staff.txt", ios::out);

    LinkList fp = head->next;
    for (int i = 0; i < head->Size; i++)
    {
        ofs << fp->Staffdata.num << " "
            << fp->Staffdata.name << " "
            << fp->Staffdata.sex << " "
            << fp->Staffdata.birthday << " "
            << fp->Staffdata.age << " "
            << fp->Staffdata.phoneNumber << " "
            << fp->Staffdata.department << " "
            << fp->Staffdata.professional_title << " "
            << fp->Staffdata.wage_scale << endl; //以空格为分界符，分别读取
        fp = fp->next;
    }
    ofs.close();
}

//程序启动时的初始化操作，需要从文件中读取文件，并保存到内存中
void readfile(LinkList &head)
{
    ifstream ifs;
    ifs.open("staff.txt", ios::in);

    //1.文件不存在
    if (!ifs.is_open())
    {
        cout << "文件不存在！" << endl;
        Init(head);
        head->Size = 0; //初始化链表
        ifs.close();
        return;
    }
    //2.正确初始化
    int num; //编号
    char name[10];
    char sex[4];
    char birthday[20];
    int age;
    char phoneNumber[11];
    char department[20];         //所属部门
    char professional_title[20]; //职称
    int wage_scale;              //工资级别

    Init(head);
    LinkList t = head;
    while (ifs >> num >> name >> sex >> birthday >> age >> phoneNumber >> department >> professional_title >> wage_scale)
    {
        LinkList s = (Node *)malloc(sizeof(Node));
        s->Staffdata.num = num;
        strcpy(s->Staffdata.name, name);
        strcpy(s->Staffdata.sex, sex);
        strcpy(s->Staffdata.birthday, birthday);
        s->Staffdata.age = age;
        strcpy(s->Staffdata.phoneNumber, phoneNumber);
        strcpy(s->Staffdata.department, department);
        strcpy(s->Staffdata.professional_title, professional_title);
        s->Staffdata.wage_scale = wage_scale;

        t->next = s;
        t = s;
        head->Size++;
    }
    t->next = NULL;
    ifs.close();
    cout << "文件初始化成功!初始化了" << head->Size << "个职工信息。" << endl;
}

int main()
{
    login();
}