#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)//��ֹ����
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 100

// ѧ���ṹ��
typedef struct {
    int studentID;              //ѧ��
    char name[MAX_NAME_LENGTH]; //����
    float chineseScore;         //����
    float mathScore;            //��ѧ
    float englishScore;         //Ӣ��
    float totalScore;           //�ܳɼ�
} Student;

// ȫ�ֱ���
Student students[MAX_STUDENTS]; // ѧ������
int numStudents = 0; // ѧ������

// ��������
void displayMenu();                     //�˵����
void processSelection(int choice);      //����ѡ��
void addStudent();                      //���ѧ����Ϣ
void displayAllStudents();              //�������ѧ����Ϣ
void sortByNameAndDisplay();            //��������
void saveStudentData();                 //�����ݽ��ļ�
void loadStudentData();                 //��ȡѧ������
void sortByTotalScoreAndDisplay();      //�ܳɼ�����
void searchStudent();                   //������ѧ�Ų���
void calculateGradeStatistics();        //�ɼ��ȼ�ͳ��
void deleteStudent();                    //ɾ��ѧ����Ϣ

int main() {
    loadStudentData(); // ���ļ��м���ѧ������

    int choice;                 //ѡ�������
    do {
        displayMenu();          //��ӡ�˵�
        scanf("%d", &choice);
        processSelection(choice);//ѡ�����
    } while (choice != 0);      //����0ʱ�˳�����

    saveStudentData(); // ����ѧ�����ݵ��ļ�
    printf("�������˳���\n");

    return 0;
}
//�˵�
void displayMenu() {
    printf("\nѧ���ɼ���ѯϵͳ\n");
    printf("-----------------\n");
    printf("1. ���ѧ���ɼ�\n");
    printf("2. ���ȫ��ѧ���ɼ�\n");
    printf("3. ��������������ɼ�\n");
    printf("4. �ɼ�����\n");
    printf("5. ������ѧ�Ų���\n");
    printf("6. �ɼ��ȼ�ͳ��\n");
    printf("7. ɾ��ѧ����Ϣ\n");
    printf("0. �˳�\n");
    printf("���������ѡ��");
}

//����ѡ��
void processSelection(int choice) {
    while (getchar() != '\n');  // ������뻺�����еĻ��з�

    switch (choice) {
        case 0:             // �˳�����
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
            printf("��Ч��ѡ�����������롣\n");
            break;
    }
}

//���ѧ����Ϣ
void addStudent() {
    if (numStudents >= MAX_STUDENTS) {
        printf("ѧ�������Ѵﵽ���ޣ��޷������ѧ����\n");
        return;
    }

    Student newStudent;
    printf("������ѧ��������\n�������\n1.������ʹ��ƴ��������ĸ��д���ɽ������������ƴ��֮��\n2.�ո�ʹ��.����\n");
    if (scanf("%s", newStudent.name) != 1) {
        printf("������������ԡ�\n");
        return;
    }
    printf("������ѧ��ѧ�ţ�");
    if (scanf("%d", &newStudent.studentID) != 1) {
        printf("������������ԡ�\n");
        return;
    }
    printf("������ѧ�����ĳɼ���");
    if (scanf("%f", &newStudent.chineseScore) != 1) {
        printf("������������ԡ�\n");
        return;
    }
    printf("������ѧ����ѧ�ɼ���");
    if (scanf("%f", &newStudent.mathScore) != 1) {
        printf("������������ԡ�\n");
        return;
    }
    printf("������ѧ��Ӣ��ɼ���");
    if (scanf("%f", &newStudent.englishScore) != 1) {
        printf("������������ԡ�\n");
        return;
    }

    // �����ܳɼ�
    newStudent.totalScore = newStudent.chineseScore + newStudent.mathScore + newStudent.englishScore;

    students[numStudents] = newStudent;
    numStudents++;

    printf("ѧ����Ϣ��ӳɹ���\n");
}

//���ȫ��ѧ����Ϣ
void displayAllStudents() {
    if (numStudents == 0) {
        printf("����ѧ����Ϣ��\n");
        return;
    }

    printf("\nȫ��ѧ���ɼ�\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܳɼ�");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }//%d����ʾ���һ��������% s����ʾ���һ���ַ�����% f����ʾ���һ���������� - ���ű�ʾ���������������ֱ�ʾ�ֶεĿ��   %-10d ��ʾ���һ��ռ��10���ַ���ȵ������������


    printf("----------------------------------------------------------------------------\n");
}

//��������
int compareNames(const void* a, const void* b);

void sortByNameAndDisplay() {
    if (numStudents == 0) {
        printf("����ѧ����Ϣ��\n");
        return;
    }

    // ��ѧ�����鰴��������
    qsort(students, numStudents, sizeof(Student), compareNames);
    //qsort()��C��׼���ṩ������������������Ҫ��������顢����Ԫ�ص�������ÿ��Ԫ�صĴ�С��һ���ȽϺ�����Ϊ�����������students����Ҫ��������飬numStudents������Ԫ�ص�������sizeof(Student)��ʾÿ��Ԫ�صĴ�С��compareNames�����ڱȽ�����ѧ�������ĺ�����
    printf("\nȫ��ѧ���ɼ�������������\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܳɼ�");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }
    printf("----------------------------------------------------------------------------\n");
}
//�Ƚ�
int compareNames(const void* a, const void* b) {
    const Student* studentA = (const Student*)a;//ʹ������ת�������� (const Student*) �� a �� b ǿ��ת��Ϊָ�� const Student ��ָ��
    const Student* studentB = (const Student*)b;//��Ϊ qsort() ����Ҫ��ȽϺ����Ĳ�������Ϊ const void*
    return strcmp(studentA->name, studentB->name);//strcmp ������ C ��׼���е�һ���ַ����ȽϺ��������ڱȽ������ַ����Ĵ�С��������������������Ҫ�Ƚϵ������ַ�����������һ������ֵ����ʾ�ȽϵĽ����
}//����ȽϺ�����������Ϊ�������������ȷ��ѧ��������ѧ����˳�򣬸����������ֵ����������

//��������
void saveStudentData() {
    FILE* file = fopen("student_data.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ�����д�롣\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%d %s %.2f %.2f %.2f %.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }

    fclose(file);
    printf("ѧ�����ݱ���ɹ���\n");
}

//��ȡ����
void loadStudentData() {
    FILE* file = fopen("student_data.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ����ж�ȡ��\n");
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
    printf("ѧ�����ݼ��سɹ���\n");
}

//�ܳɼ�����
void sortByTotalScoreAndDisplay() {
    if (numStudents == 0) {
        printf("����ѧ����Ϣ��\n");
        return;
    }

    // ʹ��ð�������㷨�����ܳɼ��Ӹߵ�������
    for (int i = 0; i < numStudents - 1; i++) {
        for (int j = 0; j < numStudents - i - 1; j++) {
            if (students[j].totalScore < students[j + 1].totalScore) {
                // ����ѧ����λ��
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    printf("\nȫ��ѧ���ɼ������ܳɼ�����\n");
    printf("----------------------------------------------------------------------------\n");
    printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܳɼ�");
    printf("----------------------------------------------------------------------------\n");
    for (int i = 0; i < numStudents; i++) {
        printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
    }
    printf("----------------------------------------------------------------------------\n");
}

//����ѧ�Ż���������ѧ���ɼ���Ϣ�����
void searchStudent() {
    if (numStudents == 0) {
        printf("����ѧ����Ϣ��\n");
        return;
    }

    int choice;
    printf("�������ѯ��ʽ��\n");
    printf("1. ����ѧ�Ų�ѯ\n");
    printf("2. ����������ѯ\n");
    printf("��ѡ���ѯ��ʽ��");
    scanf("%d", &choice);
    while (getchar() != '\n');  // ������뻺�����еĻ��з�

    if (choice == 1) {
        int studentID;
        printf("������ѧ��ѧ�ţ�");
        scanf("%d", &studentID);

        // ��ѧ�������в���ƥ���ѧ��ѧ��
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (students[i].studentID == studentID) {
                printf("\nѧ����Ϣ��ѯ���\n");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܳɼ�");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
                printf("----------------------------------------------------------------------------\n");
                found = 1;
                break;
            }
        }

        if (!found) {//����Ƿ�鵽
            printf("δ�ҵ�ƥ���ѧ��ѧ�š�\n");
        }
    }
    else if (choice == 2) {
        char name[MAX_NAME_LENGTH];
        printf("������ѧ��������");
        if (scanf("%s", name) != 1) {
            printf("������������ԡ�\n");
            return;
        }

        // ��ѧ�������в���ƥ���ѧ������
        int found = 0;
        for (int i = 0; i < numStudents; i++) {
            if (strcmp(students[i].name, name) == 0) {
                printf("\nѧ����Ϣ��ѯ���\n");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10s %-15s %-10s %-10s %-10s %-10s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܳɼ�");
                printf("----------------------------------------------------------------------------\n");
                printf("%-10d %-15s %-10.2f %-10.2f %-10.2f %-10.2f\n", students[i].studentID, students[i].name, students[i].chineseScore, students[i].mathScore, students[i].englishScore, students[i].totalScore);
                printf("----------------------------------------------------------------------------\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("δ�ҵ�ƥ���ѧ��������\n");
        }
    }
    else {
        printf("��Ч��ѡ��\n");
    }
}

//�ɼ��ȼ�ͳ��
void calculateGradeStatistics() {
    if (numStudents == 0) {
        printf("����ѧ����Ϣ��\n");
        return;
    }

    int passChineseCount = 0;      // ���ļ�������
    int goodChineseCount = 0;      // ������������
    int excellentChineseCount = 0; // ������������
    int failChineseCount = 0;      // ���Ĳ���������

    int passMathCount = 0;         // ��ѧ��������
    int goodMathCount = 0;         // ��ѧ��������
    int excellentMathCount = 0;    // ��ѧ��������
    int failMathCount = 0;         // ��ѧ����������

    int passEnglishCount = 0;      // Ӣ�Ｐ������
    int goodEnglishCount = 0;      // Ӣ����������
    int excellentEnglishCount = 0; // Ӣ����������
    int failEnglishCount = 0;      // Ӣ�ﲻ��������

    for (int i = 0; i < numStudents; i++) {
        float chineseScore = students[i].chineseScore;
        float mathScore = students[i].mathScore;
        float englishScore = students[i].englishScore;

        // ���ĳɼ��ȼ�ͳ��
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

        // ��ѧ�ɼ��ȼ�ͳ��
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

        // Ӣ��ɼ��ȼ�ͳ��
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

    //����ٷֱ�
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

    printf("\n���ĳɼ�ͳ��\n");
    printf("-----------------------------\n");
    printf("����������%d��ռ�ȣ�%.2f%%\n", passChineseCount, passChinesePercentage);
    printf("�е�������%d��ռ�ȣ�%.2f%%\n", goodChineseCount, goodChinesePercentage);
    printf("����������%d��ռ�ȣ�%.2f%%\n", excellentChineseCount, excellentChinesePercentage);
    printf("������������%d��ռ�ȣ�%.2f%%\n", failChineseCount, failChinesePercentage);
    printf("-----------------------------\n");

    printf("\n��ѧ�ɼ�ͳ��\n");
    printf("-----------------------------\n");
    printf("����������%d��ռ�ȣ�%.2f%%\n", passMathCount, passMathPercentage);
    printf("�е�������%d��ռ�ȣ�%.2f%%\n", goodMathCount, goodMathPercentage);
    printf("����������%d��ռ�ȣ�%.2f%%\n", excellentMathCount, excellentMathPercentage);
    printf("������������%d��ռ�ȣ�%.2f%%\n", failMathCount, failMathPercentage);
    printf("-----------------------------\n");

    printf("\nӢ��ɼ�ͳ��\n");
    printf("-----------------------------\n");
    printf("����������%d��ռ�ȣ�%.2f%%\n", passEnglishCount, passEnglishPercentage);
    printf("�е�������%d��ռ�ȣ�%.2f%%\n", goodEnglishCount, goodEnglishPercentage);
    printf("����������%d��ռ�ȣ�%.2f%%\n", excellentEnglishCount, excellentEnglishPercentage);
    printf("������������%d��ռ�ȣ�%.2f%%\n", failEnglishCount, failEnglishPercentage);
    printf("-----------------------------\n");
}

//ɾ��ѧ����Ϣ
void deleteStudent() {
    int studentID;
    printf("������Ҫɾ����ѧ����ѧ��: ");
    scanf("%d", &studentID);

    int index = -1;//index��ʾ��ǰɾ�������ļ��еڼ�������
    for (int i = 0; i < numStudents; i++) {
        if (students[i].studentID == studentID) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("δ�ҵ���ѧ������Ϣ\n");
    }
    else {
        // �������ѧ����Ϣ��ǰ�ƶ�
        for (int i = index; i < numStudents - 1; i++) {
            students[i] = students[i + 1];
        }
        numStudents--;
        printf("ѧ����Ϣɾ���ɹ�\n");
    }
}
