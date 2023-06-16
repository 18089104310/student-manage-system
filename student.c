#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)//防止报错
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

// 学生结构体
typedef struct {
    int studentID;              //学号
    char name[MAX_NAME_LENGTH]; //姓名
    float chineseScore;         //语文
    float mathScore;            //数学
    float englishScore;         //英语
    float totalScore;           //总成绩
} Student;

// 全局变量
Student students[MAX_STUDENTS]; // 学生数组
int numStudents = 0; // 学生数量

// 函数声明
void displayMenu();                     //菜单输出
void processSelection(int choice);      //功能选择
void addStudent();                      //添加学生信息
void displayAllStudents();              //输出所有学生信息
void sortByNameAndDisplay();            //姓名排序
void saveStudentData();                 //存数据进文件
void loadStudentData();                 //读取学生数据
void sortByTotalScoreAndDisplay();      //总成绩排名
void searchStudent();                   //姓名或学号查找
void calculateGradeStatistics();        //成绩等级统计
void deleteStudent();                    //删除学生信息

int main() {
    loadStudentData(); // 从文件中加载学生数据

    int choice;                 //选择程序功能
    do {
        displayMenu();          //打印菜单
        scanf("%d", &choice);
        processSelection(choice);//选择程序
    } while (choice != 0);      //输入0时退出程序

    saveStudentData(); // 保存学生数据到文件
    printf("程序已退出。\n");

    return 0;
}
//菜单
void displayMenu() {
    printf("\n学生成绩查询系统\n");
    printf("-----------------\n");
    printf("1. 添加学生成绩\n");
    printf("2. 输出全体学生成绩\n");
    printf("3. 按姓名排序输出成绩\n");
    printf("4. 成绩排名\n");
    printf("5. 姓名或学号查找\n");
    printf("6. 成绩等级统计\n");
    printf("7. 删除学生信息\n");
    printf("0. 退出\n");
    printf("请输入你的选择：");
}

//功能选择
void processSelection(int choice) {
    while (getchar() != '\n');  // 清除输入缓冲区中的换行符

    switch (choice) {
        case 0:             // 退出程序
            break;
        case 1:
            addStudent();
            break;
        case 2:
            displayAllStudents();
            break;
        case 3:
            sortByNameAndDisplay();
            break;
        case 4:
            sortByTotalScoreAndDisplay();
            break;
        case 5:
            searchStudent();
            break;
        case 6:
            calculateGradeStatistics();
            break;
        case 7:
            deleteStudent();
            break;

        default:
            printf("无效的选择，请重新输入。\n");
            break;
    }
}

//添加学生信息
void addStudent() {
    if (numStudents >= MAX_STUDENTS) {
        printf("学生数量已达到上限，无法添加新学生。\n");
        return;
    }

    Student newStudent;
    printf("请输入学生姓名：\n输入规则：\n1.中文名使用拼音且首字母大写（可将中文名添加至拼音之后）\n2.空格使用.代替\n");
    if (scanf("%s", newStudent.name) != 1) {
        printf("输入错误，请重试。\n");
        return;
    }
    printf("请输入学生学号：");
    if (scanf("%d", &newStudent.studentID) != 1) {
        printf("输入错误，请重试。\n");
        return;
    }
    printf("请输入学生语文成绩：");
    if (scanf("%f", &newStudent.chineseScore) != 1) {
        printf("输入错误，请重试。\n");
        return;
    }
    printf("请输入学生数学成绩：");
    if (scanf("%f", &newStudent.mathScore) != 1) {
        printf("输入错误，请重试。\n");
        return;
    }
    printf("请输入学生英语成绩：");
    if (scanf("%f", &newStudent.englishScore) != 1) {
        printf("输入错误，请重试。\n");
        return;
    }

    // 计算总成绩
    newStudent.totalScore = newStudent.chineseScore + newStudent.mathScore + newStudent.englishScore;

    students[numStudents] = newStudent;
    numStudents++;

    printf("学生信息添加成功。\n");
}

//输出全部学生信息
void displayAllStudents() {
    if (numStudents == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    printf("\n全体学生成绩\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }//%d：表示输出一个整数。% s：表示输出一个字符串。% f：表示输出一个浮点数。 - 符号表示左对齐输出，而数字表示字段的宽度   %-10d 表示输出一个占据10个字符宽度的左对齐整数。


    printf("----------------------------------------------------------------------------\n");
}

//姓名排序
int compareNames(const void* a, const void* b);

void sortByNameAndDisplay() {
    if (numStudents == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    // 对学生数组按姓名排序
    qsort(students, numStudents, sizeof(Student), compareNames);
    //qsort()是C标准库提供的排序函数，它接受需要排序的数组、数组元素的数量、每个元素的大小和一个比较函数作为参数。在这里，students是需要排序的数组，numStudents是数组元素的数量，sizeof(Student)表示每个元素的大小，compareNames是用于比较两个学生姓名的函数。
    printf("\n全体学生成绩（按姓名排序）\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }
    printf("----------------------------------------------------------------------------\n");
}
//比较
int compareNames(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;//使用类型转换操作符 (const Student*) 将 a 和 b 强制转换为指向 const Student 的指针
    const Student* studentB = (const Student*)b;//因为 qsort() 函数要求比较函数的参数类型为 const void*
    return strcmp(studentA->name, studentB->name);//strcmp 函数是 C 标准库中的一个字符串比较函数，用于比较两个字符串的大小。它接受两个参数，即要比较的两个字符串，并返回一个整数值，表示比较的结果。
}//这个比较函数的作用是为了在排序操作中确定学生数组中学生的顺序，根据姓名的字典序进行排序。

//存入数据
void saveStudentData() {
    FILE* file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("无法打开文件进行写入。\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f %.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }

    fclose(file);
    printf("学生数据保存成功。\n");
}

//读取数据
void loadStudentData() {
    FILE* file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("无法打开文件进行读取。\n");
        return;
    }

    int studentID;
    char name[MAX_NAME_LENGTH];
    float chineseScore, mathScore, englishScore, totalScore;

    while (fscanf(file, "%d %s %f %f %f %f", &studentID, name, &chineseScore, &mathScore, &englishScore, &totalScore) == 6) {
        Student newStudent;
        newStudent.studentID = studentID;
        strcpy(newStudent.name, name);
        newStudent.chineseScore = chineseScore;
        newStudent.mathScore = mathScore;
        newStudent.englishScore = englishScore;
        newStudent.totalScore = totalScore;

        students[numStudents] = newStudent;
        numStudents++;
    }

    fclose(file);
    printf("学生数据加载成功。\n");
}

//总成绩排名
void sortByTotalScoreAndDisplay() {
    if (numStudents == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    // 使用冒泡排序算法按照总成绩从高到低排序
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].totalScore < students[j + 1].totalScore) {
                // 交换学生的位置
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\n全体学生成绩（按总成绩排序）\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }
    printf("----------------------------------------------------------------------------\n");
}

//根据学号或姓名查找学生成绩信息并输出
void searchStudent() {
    if (numStudents == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    int choice;
    printf("请输入查询方式：\n");
    printf("1. 根据学号查询\n");
    printf("2. 根据姓名查询\n");
    printf("请选择查询方式：");
    scanf("%d", &choice);
    while (getchar() != '\n');  // 清除输入缓冲区中的换行符

    if (choice == 1) {
        int studentID;
        printf("请输入学生学号：");
        scanf("%d", &studentID);

        // 在学生数组中查找匹配的学生学号
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (students[i].studentID == studentID) {
                printf("\n学生信息查询结果\n");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
                printf("----------------------------------------------------------------------------\n");
                found = 1;
                break;
            }
        }

        if (!found) {//检测是否查到
            printf("未找到匹配的学生学号。\n");
        }
    }
    else if (choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("请输入学生姓名：");
        if (scanf("%s", name) != 1) {
            printf("输入错误，请重试。\n");
            return;
        }

        // 在学生数组中查找匹配的学生姓名
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("\n学生信息查询结果\n");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
                printf("----------------------------------------------------------------------------\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("未找到匹配的学生姓名。\n");
        }
    }
    else {
        printf("无效的选择。\n");
    }
}

//成绩等级统计
void calculateGradeStatistics() {
    if (numStudents == 0) {
        printf("暂无学生信息。\n");
        return;
    }

    int passChineseCount = 0;      // 语文及格人数
    int goodChineseCount = 0;      // 语文良好人数
    int excellentChineseCount = 0; // 语文优秀人数
    int failChineseCount = 0;      // 语文不及格人数

    int passMathCount = 0;         // 数学及格人数
    int goodMathCount = 0;         // 数学良好人数
    int excellentMathCount = 0;    // 数学优秀人数
    int failMathCount = 0;         // 数学不及格人数

    int passEnglishCount = 0;      // 英语及格人数
    int goodEnglishCount = 0;      // 英语良好人数
    int excellentEnglishCount = 0; // 英语优秀人数
    int failEnglishCount = 0;      // 英语不及格人数

    for (int i = 0; i < numStudents; i++) {
        float chineseScore = students[i].chineseScore;
        float mathScore = students[i].mathScore;
        float englishScore = students[i].englishScore;

        // 语文成绩等级统计
        if (chineseScore >= 60 && chineseScore < 70) {
            passChineseCount++;
        }
        else if (chineseScore >= 70 && chineseScore < 80) {
            goodChineseCount++;
        }
        else if (chineseScore >= 80) {
            excellentChineseCount++;
        }
        else {
            failChineseCount++;
        }

        // 数学成绩等级统计
        if (mathScore >= 60 && mathScore < 70) {
            passMathCount++;
        }
        else if (mathScore >= 70 && mathScore < 80) {
            goodMathCount++;
        }
        else if (mathScore >= 80) {
            excellentMathCount++;
        }
        else {
            failMathCount++;
        }

        // 英语成绩等级统计
        if (englishScore >= 60 && englishScore < 70) {
            passEnglishCount++;
        }
        else if (englishScore >= 70 && englishScore < 80) {
            goodEnglishCount++;
        }
        else if (englishScore >= 80) {
            excellentEnglishCount++;
        }
        else {
            failEnglishCount++;
        }
    }

    //计算百分比
    float passChinesePercentage = (float)passChineseCount / numStudents * 100;
    float goodChinesePercentage = (float)goodChineseCount / numStudents * 100;
    float excellentChinesePercentage = (float)excellentChineseCount / numStudents * 100;
    float failChinesePercentage = (float)failChineseCount / numStudents * 100;

    float passMathPercentage = (float)passMathCount / numStudents * 100;
    float goodMathPercentage = (float)goodMathCount / numStudents * 100;
    float excellentMathPercentage = (float)excellentMathCount / numStudents * 100;
    float failMathPercentage = (float)failMathCount / numStudents * 100;

    float passEnglishPercentage = (float)passEnglishCount / numStudents * 100;
    float goodEnglishPercentage = (float)goodEnglishCount / numStudents * 100;
    float excellentEnglishPercentage = (float)excellentEnglishCount / numStudents * 100;
    float failEnglishPercentage = (float)failEnglishCount / numStudents * 100;

    printf("\n语文成绩统计\n");
    printf("-----------------------------\n");
    printf("及格人数：%d，占比：%.2f%%\n", passChineseCount, passChinesePercentage);
    printf("中等人数：%d，占比：%.2f%%\n", goodChineseCount, goodChinesePercentage);
    printf("优秀人数：%d，占比：%.2f%%\n", excellentChineseCount, excellentChinesePercentage);
    printf("不及格人数：%d，占比：%.2f%%\n", failChineseCount, failChinesePercentage);
    printf("-----------------------------\n");

    printf("\n数学成绩统计\n");
    printf("-----------------------------\n");
    printf("及格人数：%d，占比：%.2f%%\n", passMathCount, passMathPercentage);
    printf("中等人数：%d，占比：%.2f%%\n", goodMathCount, goodMathPercentage);
    printf("优秀人数：%d，占比：%.2f%%\n", excellentMathCount, excellentMathPercentage);
    printf("不及格人数：%d，占比：%.2f%%\n", failMathCount, failMathPercentage);
    printf("-----------------------------\n");

    printf("\n英语成绩统计\n");
    printf("-----------------------------\n");
    printf("及格人数：%d，占比：%.2f%%\n", passEnglishCount, passEnglishPercentage);
    printf("中等人数：%d，占比：%.2f%%\n", goodEnglishCount, goodEnglishPercentage);
    printf("优秀人数：%d，占比：%.2f%%\n", excellentEnglishCount, excellentEnglishPercentage);
    printf("不及格人数：%d，占比：%.2f%%\n", failEnglishCount, failEnglishPercentage);
    printf("-----------------------------\n");
}

//删除学生信息
void deleteStudent() {
    int studentID;
    printf("请输入要删除的学生的学号: ");
    scanf("%d", &studentID);

    int index = -1;//index表示当前删除的是文件中第几个数据
    for (int i = 0; i < numStudents; i++) {
        if (students[i].studentID == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("未找到该学生的信息\n");
    }
    else {
        // 将后面的学生信息往前移动
        for (int i = index; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        numStudents--;
        printf("学生信息删除成功\n");
    }
}
