#include <stdio.h>
#include <string.h>
#include <windows.h>


struct Candidate{
    char name[30];
    char fname[30];
    char mname[30];
    int votes = 0;
    int password;
};

struct Voter{
    char name[30];
    int id;
    char fname[30];
    char mname[30];
    char date_of_birth[9];
    int password;
    bool voted = false;
    int mistake_counter = 4;
};

struct Candidate candidate[20];
struct Voter voter[20];
bool start = false, end = false, terminate = false, lock = false;
int candcount = 0, votercount = 0;

void admin_screen();

void candidate_screen();
int candidate_ok(int);
void candidate_input();
void candidate_withdraw(int);

void voter_screen();
void voter_input();
int voter_ok(char*);

void results();

int main(){

    if(votercount == 0)
        voter_input();

    if(terminate == true)
        return 0;

    if(start == false && end == false){
        system("cls");
        printf("             Election has not started yet.\n\n");
        printf("To go to candidate screen, enter    1\n");
        printf("To go to admin screen, enter        0\n");

        int temp;
        scanf("%d", &temp);

        if(temp == 1)
            candidate_screen();
        else
            admin_screen();
    }

    else if(start == true  && end == false){
        system("cls");
        printf("             Election is ongoing.\n\n");
        printf("To go to admin screen, enter        0\n");
        printf("To go to candidate screen, enter    1\n");
        printf("To go to voting screen, enter       2\n");

        int temp;
        scanf("%d", &temp);

        if(temp == 1)
            candidate_screen();
        else if(temp == 0)
            admin_screen();
        else if(temp == 2)
            voter_screen();
    }

    else if(start == true && end == true){
        system("cls");
        printf("             Election has ended.\n\n");
        printf("To go to admin screen, enter        0\n");
        printf("To view results, enter              1\n");

        int temp;
        scanf("%d", &temp);

        if(temp){
            results();
            printf("To go back to main screen, enter     0.\n");
            getchar();
            if(getchar())
                main();
        }
        else
            admin_screen();
    }
}





void admin_screen(){

    if(start == false && end == false){
        system("cls");

        if(candcount == 0)
            printf("             There are no candidates yet.\n");

        else{
            printf("Serial     Name\n\n");
            for(int i = 0; i < candcount; i++){
                printf("%d          %s\n", i, candidate[i].name);
            }
        }

        printf("\n\n");

        finish:
            if(start == false){
                printf("The election has not started yet.\n");
                printf("To start election, enter       1\n");
            }

            printf("To go to main screen, enter    0\n");


        bool temp;
        scanf("%d", &temp);

        if(temp){
            start = true;
            printf("You have started the election. ");
            goto finish;
        }

        else
            main();
    }

    else if(start == true && end == false){
        system("cls");

        printf("Serial     Name                     Votes\n\n");
        for(int i = 0; i < candcount; i++){
            printf("%d          ", i);
            printf("%s", candidate[i].name);
            int len = strlen(candidate[i].name);
            for(int i = 0; i < 25 - len; i++)
                printf(" ");
            printf("%d\n", candidate[i].votes);

        }

        printf("\n\n");

        if(lock == true){
            printf("The system has been lock due to multiple wrong input by a voter.\n");
            printf("Enter 1 to unlock.\n");
            int temp;
            scanf("%d", &temp);
            if(temp){
                lock = false;
                printf("You have unlocked the system.\n\n");
            }
        }

        finish1:
            if(end == false){
                printf("The election is ongoing.\n");
                printf("To end election, enter       1\n");
            }
            printf("To go to main screen, enter    0\n");

        bool temp;
        scanf("%d", &temp);

        if(temp){
            end = true;
            printf("You have ended the election. ");
            goto finish1;
        }

        else
            main();

    }

    else if(start == true && end == true){
        system("cls");
        printf("             Election has ended.\n\n");

        printf("To end program, enter          1\n");
        printf("To go to main screen, enter    0\n");

        bool temp;
        scanf("%d", &temp);

        if(temp){
            terminate = true;
            main();
        }
        else
            main();
    }
}





void candidate_screen(){

    if(start == false && end == false){

        system("cls");
        printf("             Election has not started yet.\n\n");

        printf("If you want to run for election, enter            1\n");
        printf("If you are already running for election, enter    2\n");
        printf("To go to main screen, enter                       0\n");

        int temp;
        scanf("%d", &temp);

        if(temp == 0)
            main();

        else if(temp == 1){
            candidate_input();

            printf("Press any key to go to main.\n");

            if(getchar())
                main();

        }
//
        else if(temp == 2){
            system("cls");
            Take_serial:
            int serial;
            printf("Serial: ");
            scanf("%d", &serial);

            if(candidate_ok(serial)){
                printf("Election has not started yet so you have no votes.\nYou can only withdraw from the election before the election starts.\n\n");
                printf("To withdraw, enter             1.\n");
                printf("To go to main screen, enter    0\n");

                scanf("%d", &temp);
                if(temp){
                    candidate_withdraw(serial);
                    printf("You have successfully withdrawn from the election.\n");
                    getchar();
                    printf("Press any key to go back to main screen.\n");

                    if(getchar())
                        main();
                }

                else
                    main();
            }
            else{
                printf("Wrong input.\n");
                goto Take_serial;
            }
        }

    }

    else if(start == true && end == false){
        system("cls");

        Take_serial1:
            int serial;
            printf("Serial: ");
            scanf("%d", &serial);

            if(candidate_ok(serial)){
                printf("You currently have %d votes.", candidate[serial].votes);
                printf("Press any key to go to main.\n");
                getchar();

                if(getchar())
                    main();
            }
            else{
                printf("Wrong input.\n");
                goto Take_serial1;
            }

    }
}


int candidate_ok(int serial){
    int temppassword;
    char tempname[20];

    printf("Name: ");
    getchar();
    gets(tempname);

    printf("Password: ");
    scanf("%d", &temppassword);

    return !strcmp(tempname, candidate[serial].name) && temppassword == candidate[serial].password;
}


void candidate_input(){
    system("cls");

    printf("Name: ");
    getchar();
    gets(candidate[candcount].name);

    printf("Father's Name: ");
    gets(candidate[candcount].fname);

    printf("Mother's Name: ");
    gets(candidate[candcount].mname);

    printf("Enter password: ");
    scanf("%d", &candidate[candcount].password);

    printf("\nYou have been added as a candidate. Your serial is %d.\n", candcount);
    getchar();

    candcount++;

}


void candidate_withdraw(int serial){
    for(int i = serial; i < candcount -1; i++){
        strcpy(candidate[i].name, candidate[i+1].name);
        strcpy(candidate[i].fname, candidate[i+1].fname);
        strcpy(candidate[i].mname, candidate[i+1].mname);
        candidate[i].password = candidate[i+1].password;
    }
    candcount--;
}





int index = -1;
void voter_screen(){
    system("cls");

    if(lock == true){
        printf("The system is locked. Contact admin to unlock the system.\n");
        printf("Press any key to go to main.\n");
        getchar();
        if(getchar())
            main();
    }

    else{
        char name[20];
        printf("You can only vote if all your information matches with our data base.\n");
        printf("If you want to vote, enter     1\n");
        printf("To go to main screen, enter    0\n");
        int temp;
        scanf("%d", &temp);
        getchar();
        if(temp){
            system("cls");
            printf("Name: ");

            gets(name);

            if(voter_ok(name)){
                if(voter[index].voted == true){
                    printf("You have already voted. Press any key to go back to main screen.\n");
                    getchar();
                    if(getchar())
                        main();
                }
                else{
                    printf("Serial     Name\n\n");
                    for(int i = 0; i < candcount; i++){
                        printf("%d          %s\n\n", i, candidate[i].name);
                    }

                    printf("Enter serial of the one you want to vote for: ");
                    int temp;
                    scanf("%d", &temp);
                    candidate[temp].votes++;
                    voter[index].voted = true;

                    printf("You have successfully voted.\nPress any key to go back to main screen.");
                    getchar();
                    if(getchar())
                        main();
                }

            }

            else{
                voter[index].mistake_counter--;
                printf("%d tries left.\n", voter[index].mistake_counter);
                if(voter[index].mistake_counter == 0){
                    lock = true;
                    printf("The voting system has been locked.\n");
                    printf("Contact an admin to unlock it.\n");
                }
                printf("Press any key to back go to voting screen.\n");
                getchar();
                if(getchar())
                    voter_screen();

            }
        }
        else
            main();

    }



}

FILE *input;
void voter_input(){
    input = fopen("voter_input.txt", "r");
    while(fscanf(input, "%[^\n]s", voter[votercount].name) != EOF){
        fscanf(input, "%d", &voter[votercount].id);
        fgetc(input);
        fscanf(input, "%[^\n]s", voter[votercount].fname);
        fgetc(input);
        fscanf(input, "%[^\n]s", voter[votercount].mname);
        fgetc(input);
        fscanf(input, "%[^\n]s", voter[votercount].date_of_birth);
        fscanf(input,"%d", &voter[votercount].password);
        fgetc(input);

        votercount++;
    }
    fclose(input);
}

int voter_ok(char *name){

    int id, password;
    char fname[20], mname[20], date_of_birth[20];

    printf("National ID: ");
    scanf("%d", &id);
    getchar();

    printf("Father's name: ");
    gets(fname);

    printf("Mother's name: ");
    gets(mname);

    printf("Date of Birth: ");
    gets(date_of_birth);;

    printf("Password: ");
    scanf("%d", &password);

    for(int i = 0; i < votercount; i++){
        if(strcmp(voter[i].name, name) == 0){
            index = i;
            break;
        }
    }


    if(index == -1){
        printf("Your information is not in our database. Contact election commission to be    able to vote.\n");
        printf("Press any key to go back to voter screen.\n");
        getchar();
        if(getchar())
            voter_screen();
    }

    return (strcmp(mname, voter[index].mname) == 0) && (strcmp(date_of_birth, voter[index].date_of_birth) == 0) && (id == voter[index].id) && (password == voter[index].password);
}





void results(){
    system("cls");

    for(int i = 0; i < candcount; i++){
        for(int j = 0; j < candcount; j++){
            if(candidate[j].votes < candidate[i].votes){
                char temp[20];
                int tem;

                strcpy(temp, candidate[i].name);
                strcpy(candidate[i].name, candidate[j].name);
                strcpy(candidate[j].name, temp);

                strcpy(temp, candidate[i].fname);
                strcpy(candidate[i].fname, candidate[j].fname);
                strcpy(candidate[j].fname, temp);

                strcpy(temp, candidate[i].mname);
                strcpy(candidate[i].mname, candidate[j].mname);
                strcpy(candidate[j].mname, temp);

                candidate[i].votes += candidate[j].votes;
                candidate[j].votes = candidate[i].votes - candidate[j].votes;
                candidate[i].votes -= candidate[j].votes;

                candidate[i].password += candidate[j].password;
                candidate[j].password = candidate[i].password - candidate[j].password;
                candidate[i].password -= candidate[j].password;
            }
        }
    }

    printf("Rank     Name                     Votes\n\n");
    for(int i = 0; i < candcount; i++){
        printf("%d          ", i+1);
        printf("%s", candidate[i].name);
        int len = strlen(candidate[i].name);
        for(int i = 0; i < 25 - len; i++)
            printf(" ");
        printf("%d\n", candidate[i].votes);
        }

}







