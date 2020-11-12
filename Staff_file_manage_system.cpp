#include <iostream>
#include <malloc.h>
#include <string.h>
#include <fstream>
#define PassWord "admin123"
using namespace std;

struct Staff_Info
{
    int num; //���
    char name[10];
    char sex[4];
    char birthday[20];
    int age;
    char phoneNumber[11];
    char department[20];         //��������
    char professional_title[20]; //ְ��
    int wage_scale;              //���ʼ�����1��2��3��4��
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
    cout << "��ӭ����ְ����������ϵͳ!" << endl;
    cout << "��ѡ����Ҫ��¼�ķ�ʽ��" << endl;
    cout << "1----->�ο͵�¼" << endl;
    cout << "2----->����Ա��¼" << endl;
    cout << "0----->�˳�ϵͳ" << endl;
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
            cout << "�����˳�ϵͳ�����Ժ�..." << endl;
            system("pause");
            exit(0);
        default:
            cout << "�����������������룡" << endl;
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
    free(sta); //�ͷ�ͷ�ڵ�
}

void adminBackground()
{
    char root[20];
    char password[20];

    char _root[20];
    char _password[20];

    ifstream ifs;
    ifs.open("Administrator_Info.txt", ios::in);

    if (!ifs.is_open()) //�洢����Ա���ļ���δ����
    {
        cout << "����Ա��Ϣ��δ����!�뽨�������ԡ�" << endl;
        cout << "�����˳�ϵͳ..." << endl;
        system("pause");
        exit(0);
    }

    while (1)
    {
        int flag=0;
        cout << "���������Ա�˺ţ�" << endl;
        cin >> root;
        cout << "���������Ա���룺" << endl;
        cin >> password;
        while (ifs >> _root >> _password)
        {
            if (!strcmp(_root, root) && !strcmp(_password, password)) //�˺ź�����ͬʱ��ȷ
            {
                flag=1;
                cout << "��½�ɹ���" << endl;
                system("pause");
                break;
            }
        }
        cout << "������˺Ż�������������������!" << endl;
        ifs.clear();//�����״̬��־
        ifs.seekg(0,ios::beg);//��ָ�����¶�λ���ļ���ͷ
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
    free(sta); //�ͷ�ͷ�ڵ�
}

void showMenu()
{
    cout << "\t\t***************ְ����������ϵͳ************" << endl;
    cout << "\t\t\t\t1��¼��ְ����Ϣ" << endl;
    cout << "\t\t\t\t2����ʾְ����Ϣ" << endl;
    cout << "\t\t\t\t3��ɾ��ְ����Ϣ" << endl;
    cout << "\t\t\t\t4������ְ����Ϣ" << endl;
    cout << "\t\t\t\t5���޸�ְ����Ϣ" << endl;
    cout << "\t\t\t\t6������" << endl;
    cout << "\t\t\t\t7�����ȫ��ְ��" << endl;
    cout << "\t\t\t\t0���˳�ϵͳ\n"
         << endl;
    cout << "\t\t------> ��ѡ����������������ţ�";
}

void showPart_Menu()
{
    cout << "\t\t***************ְ����������ϵͳ************" << endl;
    cout << "\t\t\t\t1����ʾְ����Ϣ" << endl;
    cout << "\t\t\t\t2������ְ����Ϣ" << endl;
    cout << "\t\t\t\t0���˳�ϵͳ\n"
         << endl;
    cout << "\t\t------> ��ѡ����������������ţ�";
}

void exitSystem()
{
    cout << "��ӭ�´�ʹ�ã��ټ���" << endl;
    system("pause");
    exit(0);
}

void Init(LinkList &head) //��ʼ������
{
    head = (Node *)malloc(sizeof(Node));
    head->next = NULL;
    head->Size = 0;
}

void printStaffInfo(Staff_Info *cur)
{
    cout << "��ţ�" << cur->num;
    cout << "  ������" << cur->name;
    cout << "  �Ա�" << cur->sex;
    cout << "  ���գ�" << cur->birthday;
    cout << "  ���䣺" << cur->age;
    cout << "  �绰��" << cur->phoneNumber;
    cout << "  �������ţ�" << cur->department;
    cout << "  ְ�ƣ�" << cur->professional_title;
    cout << "  ���ʼ���" << cur->wage_scale << endl;
} //�����������Ļ���

void addStaff(LinkList &head)
{
    LinkList t = head;
    cout << "��������Ҫ��ӵ�ְ��������";
    int count = 0;
    cin >> count;
    while (t->next != NULL)
    {
        t = t->next;
    } //��ʼ��ֵʱ��ʹt��Զָ����������һ���ڵ�

    ofstream ofs;
    ofs.open("staff.txt", ios::out | ios::app); //��׷�ӷ�ʽд���ļ�

    if (!ofs.is_open())
    {
        cout << "�ļ���ʧ�ܣ�" << endl;
        system("pause");
        system("cls");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        LinkList s = (Node *)malloc(sizeof(Node));

        cout << "������ְ���ı�ţ�";
        cin >> s->Staffdata.num;
        cout << "������ְ����������";
        cin >> s->Staffdata.name;
        cout << "������ְ�����Ա�";
        cin >> s->Staffdata.sex;
        cout << "������ְ�������գ���1999��03��14�գ���";
        cin >> s->Staffdata.birthday;
        cout << "������ְ�������䣺";
        cin >> s->Staffdata.age;
        cout << "������ְ���ĵ绰��";
        cin >> s->Staffdata.phoneNumber;
        cout << "������ְ���ĵ绰�������ţ�";
        cin >> s->Staffdata.department;
        cout << "������ְ����ְ�ƣ�";
        cin >> s->Staffdata.professional_title;
        cout << "������ְ���Ĺ��ʼ���";
        cin >> s->Staffdata.wage_scale;

        ofs << s->Staffdata.num << " "
            << s->Staffdata.name << " "
            << s->Staffdata.sex << " "
            << s->Staffdata.birthday << " "
            << s->Staffdata.age << " "
            << s->Staffdata.phoneNumber << " "
            << s->Staffdata.department << " "
            << s->Staffdata.professional_title << " "
            << s->Staffdata.wage_scale << endl; //�Կո�Ϊ�ֽ�����ֱ��ȡ

        t->next = s;
        t = s;
        head->Size++;
        cout << "¼����ɣ�" << endl;
    }
    t->next = NULL;
    ofs.close();
    cout << "ְ����Ϣ¼����ɣ����ι�¼��" << count << "��ְ����Ϣ,����" << head->Size << "��ְ����Ϣ." << endl;
    system("pause");
    system("cls");
}

void showStaffList(LinkList head)
{
    system("cls");
    if (head->Size == 0)
    {
        cout << "û��ְ����Ϣ��" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����ʾ" << head->Size << "��ְ����Ϣ" << endl;
    cout << "��" << endl;
    LinkList p = head->next;
    int count = 0; //����ʵ��10��10�е���������������ʾ��һҳ
    int page = 0;  //��ǰҳ��
    int sumpage;   //�ܹ�ҳ��
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
            cout << "ҳ����" << page << "/" << sumpage << endl;
            system("pause");
            system("cls");
        }
    }
    if (head->Size % 10 != 0)
    {
        cout << "ҳ����" << page + 1 << "/" << sumpage << endl;
        system("pause");
        system("cls");
    }
}

LinkList isExist(LinkList head, char *name)
{
    LinkList p = head->next;
    LinkList pre = head;
    for (int i = 0; i < head->Size && strcmp(p->Staffdata.name, name); i++) //�Ƚ����ַ����������ʱ����ѭ��
    {
        p = p->next;
        pre = pre->next;
    }
    if (p == NULL) //�Ҳ���
    {
        return NULL;
    }
    return pre; //�ҵ�����ǰ�̽ڵ�
}

bool secondPassword() //��������
{
    cout << "���������룺" << endl;
    char password[20];
    int times = 4;
    cin >> password;
    while (strcmp(password, PassWord))
    {
        if (times == 0)
        {
            cout << "��������Ѵ����ޣ������˳���ѡ��..." << endl;
            system("pause");
            system("cls");
            return false;
        }
        cout << "����������ٴ����룡�㻹��" << times << "��������ᡣ" << endl;
        times--;
        cin >> password;
    }
    return true;
}

void delStaffByName(LinkList &head)
{
    if (!secondPassword()) //��������ʧ�ܷ���
        return;
    cout << "������Ҫɾ����ְ����������";
    char name[20];
    cin >> name;
    LinkList pos = isExist(head, name); //�ж�ְ�����������Ƿ���ڣ������ڲ���������ǰ��ָ�룬�������򷵻�NULL
    if (pos == NULL)
    {
        cout << "��ְ�������ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        LinkList d = pos->next; //dΪ��ɾ���ڵ�
        pos->next = pos->next->next;
        free(d);
        cout << "ɾ����ɣ�" << endl;
        head->Size--;
        savefile(head); //ɾ�������±����ļ�
        system("pause");
        system("cls");
    }
}

void findStaffByName(LinkList head) //���ҷ��ϸ����ֵ�����ְ��
{
    cout << "������Ҫ���ҵ�ְ����������";
    char name[20];
    cin >> name;
    int count = 0;

    LinkList p = head->next;
    while (p != NULL)
    {
        if (!strcmp(p->Staffdata.name, name)) //����ƥ��ʱ������Ϊ��
        {
            printStaffInfo(&(p->Staffdata));
            count++;
        }
        p = p->next; //��ƥ��ָ�����
    }
    if (count == 0)
    {
        cout << "����Ϊ" << name << "��ְ�������ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    cout << "����ʾ" << count << "������Ϊ" << name << "��ְ����Ϣ��" << endl;
    system("pause");
    system("cls");
}

void sortStaffByNum(LinkList &head)
{
    cout << "��ѡ�񰴱�������˳�򣨰�0��ʾ��С���󣬰�1��ʾ�Ӵ�С����";
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
            cout << "������ɣ�" << endl;
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
            cout << "������ɣ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        cout << "�����������������룡" << endl;
    }
}

void sortStaffByWage(LinkList &head)
{
    cout << "��ѡ�񰴹��ʼ��������˳�򣨰�0��ʾ��С���󣬰�1��ʾ�Ӵ�С����";
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
            cout << "������ɣ�" << endl;
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
            cout << "������ɣ�" << endl;
            system("pause");
            system("cls");
            return;
        }
        cout << "�����������������룡" << endl;
    }
}

void sortStaff(LinkList &head)
{
    cout << "��ѡ������ķ�ʽ��" << endl;
    cout << "1.���������" << endl;
    cout << "2.�����ʼ�������" << endl;
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
            cout << "�����������������룡" << endl;
            break;
        }
    }
}
void updateStaffByName(LinkList &head)
{
    if (!secondPassword()) //��������ʧ�ܷ���
        return;
    cout << "��������Ҫ�޸ĵ�ְ����������";
    char name[20];
    cin >> name;
    LinkList pos = isExist(head, name);
    if (pos == NULL)
    {
        cout << "��ְ�������ڣ�" << endl;
        system("pause");
        system("cls");
        return;
    }
    else
    {
        cout << "������ְ���ı�ţ�";
        cin >> pos->next->Staffdata.num;
        cout << "������ְ����������";
        cin >> pos->next->Staffdata.name;
        cout << "������ְ�����Ա�";
        cin >> pos->next->Staffdata.sex;
        cout << "������ְ�������գ���1999��03��14�գ���";
        cin >> pos->next->Staffdata.birthday;
        cout << "������ְ�������䣺";
        cin >> pos->next->Staffdata.age;
        cout << "������ְ���ĵ绰��";
        cin >> pos->next->Staffdata.phoneNumber;
        cout << "������ְ���ĵ绰�������ţ�";
        cin >> pos->next->Staffdata.department;
        cout << "������ְ����ְ�ƣ�";
        cin >> pos->next->Staffdata.professional_title;
        cout << "������ְ���Ĺ��ʼ���";
        cin >> pos->next->Staffdata.wage_scale;
        savefile(head);
        system("pause");
        system("cls");
    }
}

void clearStaff(LinkList &head) //���ͷ�ͷ�ڵ㣬ֻ�ͷź�̵����нڵ�
{
    if (!secondPassword()) //��������ʧ�ܷ���
        return;
    LinkList p = head->next;
    LinkList pre = p;
    while (p != NULL)
    {
        p = p->next;
        free(pre); //�ͷ�
        pre = p;
    }
    free(pre);
    head->Size = 0;
    head->next = NULL;
    savefile(head);
    cout << "ְ����Ϣ����գ�" << endl;
    system("pause");
    system("cls");
}

//�����ļ�����
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
            << fp->Staffdata.wage_scale << endl; //�Կո�Ϊ�ֽ�����ֱ��ȡ
        fp = fp->next;
    }
    ofs.close();
}

//��������ʱ�ĳ�ʼ����������Ҫ���ļ��ж�ȡ�ļ��������浽�ڴ���
void readfile(LinkList &head)
{
    ifstream ifs;
    ifs.open("staff.txt", ios::in);

    //1.�ļ�������
    if (!ifs.is_open())
    {
        cout << "�ļ������ڣ�" << endl;
        Init(head);
        head->Size = 0; //��ʼ������
        ifs.close();
        return;
    }
    //2.��ȷ��ʼ��
    int num; //���
    char name[10];
    char sex[4];
    char birthday[20];
    int age;
    char phoneNumber[11];
    char department[20];         //��������
    char professional_title[20]; //ְ��
    int wage_scale;              //���ʼ���

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
    cout << "�ļ���ʼ���ɹ�!��ʼ����" << head->Size << "��ְ����Ϣ��" << endl;
}

int main()
{
    login();
}