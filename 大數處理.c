//大數運算 2022-03-01 陳科融
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<memory.h>
#include<stdbool.h>
char first[9999]={'\0'};
char second[9999]={'\0'};
int borrow=10,carry=0;
int f_size;
int s_size;
int div_ans[9999];
int div_size[9999];
int point_of_decimal[9999];
int point_size[9999];
//==================<除法翻轉>======================
void div_reverse(char list[]){
    char set[9999]={'\0'};
    int cnt=0;
    for(int x=strlen(list)-1;x>=0;x--){
        set[cnt]=list[x];
        cnt+=1;
    }
    memset(list,'\0',sizeof(char)*9999);
    strcpy(list,set);
}
//================<強制轉成int>=====================
void change_int(char list[]){
    char save_int[9999]={'\0'};
    int ok=0;
    int cnt=0;
    for(int x=0;x<strlen(list);x++){
        if(list[x]!='0'){
            ok=1;
        }
        if(ok==1){
            save_int[cnt]=list[x];
            cnt+=1;
        }
    }
    memset(list,'\0',sizeof(char)*9999);
    strcpy(list,save_int);
}
//===================<交換>=====================
void change(char change[],char list[]){
    int size=strlen(list);
    for(int x=0;x<size;x++){
        change[x]=list[x];
    }
}
//===================<翻轉>=====================
void reverse(char list[],char rev[]){
    int cnt=0;
    for(int x=strlen(list)-1;x>=0;x--){
        rev[cnt]=list[x];
        cnt+=1;
    }
}
//===================<加法>=====================
int add(char first[],char second[],int answer[]){
    int run=0;
    int f_size=strlen(first);
    int s_size=strlen(second);
    for(int x=0;x<99999;x++){
        if(first[x]=='\0' && second[x]=='\0' && carry ==0){
            return run;
        }
        else{
            if(first[x]>='0'){
                first[x]=first[x]-'0';
            }
            if(second[x]>='0'){
                second[x]=second[x]-'0';
            }
            answer[x]=(first[x]+second[x]+carry)%10;
            carry=(first[x]+second[x]+carry)/10;
            run+=1;
        }
    }
}
//==================<減法>=========================
int minus(char first[],char second[],int answer[]){
    int run=0;
    int f_size=strlen(first);
    int s_size=strlen(second);
    for(int x=0;x<9999;x++){
        if(first[x]=='\0' && second[x]=='\0'){
            return run;
        }
        else{
            if(first[x]>='0'){
                first[x]=first[x]-'0';
            }
            if(second[x]>='0'){
                second[x]=second[x]-'0';
            }
            if(first[x]>=second[x]){
                answer[x]=first[x]-second[x];
                run+=1;
            }
            else if(first[x]<second[x]){
                answer[x]=borrow-second[x]+first[x];
                int cnt=1;
                while(first[cnt+x]=='0'){
                    first[cnt+x]+=9;
                    cnt+=1;
                }
                first[x+cnt]-=1;
                run+=1;
            }
        }
    }
}
//===================<乘法>=====================
void multiply(char first[],char second[],int answer[]){
    int carry=0;
    int f_size=strlen(first);
    int s_size=strlen(second);
    int max_size=f_size+s_size;
    int **save=(int **)calloc(9999,sizeof(int*));
    for(int x=0;x<max_size;x++){
        save[x]=(int *)calloc(9999,sizeof(int));
    }
    for(int x=0;x<f_size;x++){
        for(int y=0;y<s_size;y++){
            save[x][y]=((first[x]-'0')*(second[y]-'0'));
        }
    }
    for(int x=0;x<f_size;x++){
        int cnt=0;
        for(int y=x;y<max_size;y++){
            if(cnt==s_size){
                continue;
            }
            else{
                answer[y]+=save[x][cnt];
                cnt+=1;
            }
        }
    }
    for(int x=0;x<max_size;x++){
        if(answer[x]>=10){
            carry=answer[x]/10;
            answer[x]%=10;
            answer[x+1]+=carry;
        }
    }
    int ok=0;
    for(int x=max_size;x>=0;x--){
        if(answer[x]!=0){
            ok=1;
        }
        if(ok==1){
            printf("%d",answer[x]);
        }
    }

    for(int i=0;i<9999;i++){
        free(save[i]);
    }
    free(save);
}
//=================<除法的減法>===================
void div_sub(char first[],char change_second[]){
    char sub_result[9999]={'\0'};    //減法結果
//    printf("被除數(%s),",first);
//    printf("除數(%s)\n",change_second);
    div_reverse(first);             //翻轉做減法
    div_reverse(change_second);     //翻轉做減法
    for(int x=0;x<9999;x++){
        if(first[x]=='\0' && change_second[x]=='\0'){
            break;                  //減法終止
        }
        else{
            if(first[x]>=change_second[x]){
                if(change_second[x]=='\0'){
                    sub_result[x]=first[x];
                }
                else{
                    sub_result[x]=first[x]-change_second[x]+'0';//被除數第x位夠減除數第x位
                }
            }
            else{
                sub_result[x]=10-change_second[x]+first[x]+'0';//借位
                int cnt=1;
                while(first[x+cnt]=='0'){                   //借位的那位等於0
                    first[x+cnt]+=9;
                    cnt+=1;                                 //多借到第幾位
                }
                first[x+cnt]-=1;
            }
        }
    }
    div_reverse(sub_result);                                //翻轉回來
    change_int(sub_result);                                 //轉成int
    memset(first,'\0',sizeof(char)*9999);
    strcpy(first,sub_result);
}
//===================<主程式>=====================
int main(){
    char operation[1];
    while(scanf("%s%s%s",first,&operation[0],second)!=EOF){
        char R_first[9999]={'\0'};
        char R_second[9999]={'\0'};
        char div[9999]={'\0'};
        int *answer=(int *)calloc(9999,sizeof(int));
//==================<加法動作>=====================
        if(operation[0]=='+'){
            reverse(first,R_first);
            reverse(second,R_second);
            int run=add(R_first,R_second,answer);
            for(int x=run-1;x>=0;x--){
                printf("%d",answer[x]);
            }
        }
//==================<減法動作>=====================
        if(operation[0]=='-'){
            f_size=strlen(first);
            s_size=strlen(second);
            if(f_size>s_size){//減數遠比被減數大
                reverse(first,R_first);
                reverse(second,R_second);
                int run=minus(R_first,R_second,answer);
                for(int x=run-1;x>=0;x--){
                    printf("%d",answer[x]);
                }
            }
            else if(f_size==s_size){//減數根被減數位數相同
                int not_big=0;
                for(int x=0;x<f_size;x++){
                    if(first[x]>second[x]){
                        break;
                    }
                    else if(first[x]==second[x]){
                        continue;
                    }
                    else{
                        not_big=1;
                    }
                }
                if(not_big==1){//減數比被減數小
                    reverse(first,R_first);
                    reverse(second,R_second);
                    char change_f[9999]={'\0'};
                    char change_s[9999]={'\0'};
                    change(change_f,R_second);
                    change(change_s,R_first);
                    int run=minus(change_f,change_s,answer);
                    printf("-");
                    int ok=0;
                    for(int x=run-1;x>=0;x--){
                        if(answer[x]!=0){
                            ok=1;
                        }
                        if(ok==1){
                            printf("%d",answer[x]);
                        }
                    }
                }
                else{//減數大於被減數
                    reverse(first,R_first);
                    reverse(second,R_second);
                    int run=minus(R_first,R_second,answer);
                    int ok=0;
                    for(int x=run-1;x>=0;x--){
                        if(answer[x]!=0){
                            ok=1;
                        }
                        if(ok==1){
                            printf("%d",answer[x]);
                        }
                        if(x==0 && ok==0){
                            printf("0");
                        }
                    }
                }
            }
            else if(f_size<s_size){//減數比被減數位數少
                reverse(first,R_first);
                reverse(second,R_second);
                char change_f[9999]={'\0'};
                char change_s[9999]={'\0'};
                change(change_f,R_second);
                change(change_s,R_first);
                int run=minus(change_f,change_s,answer);
                printf("-");
                for(int x=run-1;x>=0;x--){
                    printf("%d",answer[x]);
                }
            }
        }
//==================<乘法動作>=====================
        if(operation[0]=='*'){
            reverse(first,R_first);
            reverse(second,R_second);
            multiply(R_first,R_second,answer);
        }
//==================<除法動作>=====================
/*9194871398571384 / 187497325325143*/
        if(operation[0]=='/'){
            int other=0;
            if((strlen(first)==strlen(second) &&strcmp(first,second)<0)|| strlen(first)<strlen(second)){
                other=1;    //小數
            }
            int old_first_size=strlen(first);
            int ans_size=old_first_size-strlen(second);
            int size=strlen(first)-strlen(second);
            char second_judge[999]={'\0'};
            strcpy(second_judge,second);
            for(int x=0;x<size;x++){
                strcat(second_judge,"0");
            }
            int ok=1;
            if(strcmp(first,second_judge)>=0){
                ans_size+=1;
            }
            if(strlen(first)==strlen(second)&&strcmp(first,second)==0){
                printf("1\n");
                continue;
            }
            int decimal_zero=0;
            if(strlen(first)==strlen(second)&&strcmp(first,second)>0){
                size+=1;
            }
            int add=0;
            char change_second[9999]={'\0'};      //用來存(變化的除數)
            int run=0;
            if(first[0]=='0') change_int(first);  //強制轉型int
            if(second[0]=='0') change_int(second);//強制轉型int
            while((strlen(first)>strlen(second))||strcmp(first,second)>=0){      //被除數比除數大時要進行動作
                if((strlen(first)==strlen(second))&&strcmp(first,second)<0) break;//終止條件
                if((strlen(first)<strlen(second))){
                    break;                       //被除數比除數小時，終止
                }
                int f_len=strlen(first);         //被除數長度
                int s_len=strlen(second);        //除數長度
                int can=1;                       //第一次判斷，做補0動作
                if(f_len>=s_len && can==1){
                    strcpy(change_second,second);//用來存變動的除數
                    for(int x=0;x<f_len-s_len;x++){
                        strcat(change_second,"0");
                    }
                }
                if((strcmp(first,change_second)>=0) && strlen(change_second)>=strlen(second)){
                    div_sub(first,change_second); //被除數大於變化的除數，進行除法的減法動作
                }
                else{
                    change_second[strlen(change_second)-1]='\0';//如果不是，則清掉多的0
                    div_sub(first,change_second);
                }
                div_size[run]=strlen(change_second);
                run+=1;
            }
            if(strlen(first)<strlen(second)){
                decimal_zero=strlen(change_second)-strlen(second);
            }
            int max=div_size[0];
            int cnt=0;
            int ans_run_size=0;
            for(int x=0;x<run;x++){
                if(max==div_size[x]){
                    div_ans[cnt]+=1;
                }
                else{
                    int minus=max-div_size[x];
                    cnt+=minus;
                    div_ans[cnt]++;
                    max=div_size[x];
                    ans_run_size+=minus;
                }
            }
            for(int x=0;x<ans_size;x++){
                printf("%d",div_ans[x]);
            }
//==================<小數處理>=====================
            if(other==1){
                printf("0");
            }
            int zero_size=0;
            char judge_first[999]={'\0'};
            strcpy(judge_first,first);
            if(strlen(first)<strlen(second)){
                for(int x=1;x<=strlen(second)-strlen(first);x++){
                    strcat(judge_first,"0");
                }
                if(strcmp(judge_first,second)<0){
                    zero_size=strlen(second)-strlen(first);
                }
                else if(strcmp(judge_first,second)>=0){
                    zero_size=strlen(second)-strlen(first)-1;
                }
            }
            if(first[0]!='\0'){                 //偵測有要做小數
                for(int x=0;x<10;x++){
                    strcat(first,"0");
                }
                int old_first_size=strlen(first);
                int point_run=0;
                char change_second[9999]={'\0'};
                while((strlen(first)>strlen(second))||strcmp(first,second)>=0){
                    if((strlen(first)==strlen(second))&&strcmp(first,second)<0) break;//終止條件
                    if((strlen(first)<strlen(second))) break;
                    int f_len=strlen(first);
                    int s_len=strlen(second);
                    if(f_len>=s_len){
                        strcpy(change_second,second);
                        for(int x=0;x<f_len-s_len;x++){
                            strcat(change_second,"0");
                        }
                    }
                    if((strcmp(first,change_second)>=0) && strlen(change_second)>=strlen(second)){
                        div_sub(first,change_second);
                    }
                    else{
                        change_second[strlen(change_second)-1]='\0';
                        div_sub(first,change_second);
                    }
                    point_size[point_run]=strlen(change_second);
                    point_run+=1;
                }
                printf(".");
                int max=point_size[0];
                int cnt=0;
                int ans_run_size=0;
                for(int x=0;x<point_run;x++){
                    if(max==point_size[x]){
                        point_of_decimal[cnt]+=1;
                    }
                    else{
                        int minus=max-point_size[x];
                        cnt+=minus;
                        point_of_decimal[cnt]++;
                        max=point_size[x];
                        ans_run_size+=minus;
                    }
                }
                for(int x=0;x<zero_size;x++){
                    printf("0");
                }
                for(int x=0;x<=ans_run_size;x++){
                    printf("%d",point_of_decimal[x]);
                }
            }
        }
        printf("\n");
        memset(div_ans,0,sizeof(int)*9999);
        memset(point_of_decimal,0,sizeof(int)*9999);
        memset(first,'\0',sizeof(char)*9999);
        memset(second,'\0',sizeof(char)*9999);
        memset(R_first,'\0',sizeof(char)*9999);
        memset(R_second,'\0',sizeof(char)*9999);
        free(answer);
    }
    return 0;
}
