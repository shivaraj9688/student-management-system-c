#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Student{
    int id;
    char name[50];
    float marks;
};

void add_student(){
    FILE *fp = fopen("student.txt","ab");
    struct Student s;

    printf("Enter ID: ");
    scanf("%d",&s.id);

    printf("Enter name: ");
    getchar();
    fgets(s.name,sizeof(s.name),stdin);
    s.name[strcspn(s.name,"\n")] = 0;

    printf("Enter marks: ");
    scanf("%f",&s.marks);

    fwrite(&s,sizeof(s),1,fp);
    fclose(fp);

    printf("Student added successfully.\n");
}

void view_students(){
    FILE *fp = fopen("student.txt","rb");
    struct Student s;

    if(fp == NULL){
        printf("No data found\n");
        return;
    }

    printf("\n---Student list---\n");

    while (fread(&s,sizeof(s),1,fp)){
        printf("ID: %d | Name: %s | Marks: %.2f\n",s.id,s.name,s.marks);
    }

    fclose(fp);
}

void searchstudent(){
    FILE *fp = fopen("student.txt","rb");
    struct Student s;
    int id, found = 0;

    if(fp == NULL){
        printf("No data found\n");
        return;
    }

    printf("Enter ID to search: ");
    scanf("%d",&id);

    while (fread(&s,sizeof(s),1,fp)){
        if (s.id == id){
            printf("Found -> ID: %d | Name: %s | Marks: %.2f\n",s.id,s.name,s.marks);
            found = 1;
            break;
        }
    }

    if(!found){
        printf("Student not found\n");
    }

    fclose(fp);
}

void deletestudent(){
    FILE *fp = fopen("student.txt","rb");
    FILE *temp = fopen("temp.txt","wb");

    struct Student s;
    int id, found = 0;

    if(fp == NULL){
        printf("No data found\n");
        return;
    }

    printf("Enter id to be deleted: ");
    scanf("%d",&id);

    while (fread(&s,sizeof(s),1,fp)){
        if (s.id != id){
            fwrite(&s,sizeof(s),1,temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("student.txt");
    rename("temp.txt","student.txt");

    if(found){
        printf("Student deleted successfully\n");
    } else {
        printf("Student not found\n");
    }
}

int main(){
    int choice;

    while (1){
        printf("\n---Student Management System---\n"); 
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch (choice){
            case 1: add_student(); break;
            case 2: view_students(); break;
            case 3: searchstudent(); break;
            case 4: deletestudent(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}