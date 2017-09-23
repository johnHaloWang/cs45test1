#include <iostream>
#include <string>
#define PASS 1;
#define INPUT_ERROR_DEFINE1  2;
#define MISSING_PARENTHESIS1 3;
#define UNKNOW_ERROR 4;
using namespace std;

void init(int list[128], char u[16][10]);
void show(unsigned int enterSet[52][17], char u[16][10]);

unsigned int sizeArr(char arr[5000]);
void nukeArr(char arr[5000]);
bool emptyArr(char arr[5000]);

void shiftStackBack(char stack[5000]);
void pushStack(char item, char stack[5000]);
char topStack(char stack[5000]);
void popStack(char stack[5000]);


char frontQueue(char queue[5000]);
char backQueue(char queue[5000]);
void pushQueue(char item, char queue[5000]);
void popQueue(char queue[5000]);

bool throwing_INPUT_EMPTY();
bool throwing_INPUT_ERROR();
bool throwing_MISSING_PARENTHESIS();
bool throwing_UNKNOW_ERROR();
bool throwing_NO_MEMORY_ERROR();
bool throwing_need_space_ERROR();
bool throwing_INPUT_EMPTY_NO_SPACE_BEFORE_SET();

void subStr(char arr[5000], int index, int index1);
int subStrInsert(char arr[5000], int index, int index1, int replace);
/* 00000 */
unsigned int validation(int list[128], char input[], char u[16][10]);
unsigned short int readExpression(int list[128], unsigned int enterSet[52][17],char stack[], char queue[], char input[5000], char RPN[5000]);

int main()
{
    int list[128];
    unsigned int enterSet[52][17];
    char universe[16][10];
    char stack[5000]={'\0'};
    char queue[5000]={'\0'};
    char RPN[5000];
    init(list, universe);
    char input[]={'\0'};
      cout<<"enter: ";
      cin.getline(input, 5000);
      cout<<input<<endl;
    validation(list, input, universe);
    cout<<input<<endl;
    readExpression(list, enterSet, stack, queue, input, RPN);
    return 0;
}
/* char arr utility function */
unsigned int sizeArr(char arr[5000])
{
  unsigned int limit=0;
  for(;arr[limit]!='\0';limit++);
  return limit;
}
void nukeArr(char arr[5000])
{
    arr[0]='\0';
}
bool emptyArr(char arr[5000])
{
    return arr[0]=='\0';
}
/* char queue utility function */
char frontQueue(char queue[5000])
{
    return queue[0];
}
char backQueue(char queue[5000])
{
    return queue[sizeArr(queue)-1];
}
void pushQueue(char item, char queue[5000])
{
    unsigned int index = sizeArr(queue);
    queue[index]=item;
    queue[index+1]='\0';
}
void popQueue(char queue[5000])
{
    for(unsigned int i = 0;queue[i]!='\0';queue[i]=queue[i+1], i++);
}
/* char stack utility function */
void shiftStackBack(char stack[5000])
{
    int limit = 0;
    for(;stack[limit]!='\0';limit++);
    for(;limit>=0;stack[limit+1]=stack[limit], limit--);
}
void pushStack(char item, char stack[5000])
{
    if(stack[0]=='\0')
        stack[1]='\0';
    else
        shiftStackBack(stack);
     stack[0]=item;
}
char topStack(char stack[5000])
{
    return stack[0];
}
void popStack(char stack[5000])
{
    for(unsigned int i = 0;stack[i]!='\0';stack[i]=stack[i+1],i++);
}
unsigned short int readExpression(int list[128], unsigned int enterSet[52][17],char stack[], char queue[], char input[5000], char RPN[5000])
{
  cout<<"fired...readExpress"<<endl;
  unsigned int i=0;
  int intExpCount=0;
  while(input[i])
  {

      if((list[(int)input[i]]==0)&&(throwing_INPUT_ERROR()))
      {
          return INPUT_ERROR_DEFINE1; //return 22
      }
      if(list[(int)input[i]]==1)
      {
          if((input[i+1]!='\0') && list[(int)input[i+1]]==1)
          {
              throwing_INPUT_ERROR();
              return INPUT_ERROR_DEFINE1;
          }
          pushQueue(input[i], queue);
      }
      else if(list[(int)input[i]]==4)//={} case//4 ia {
      {
          unsigned int pointTo=0, pointToBit=0, endP=1;
          char temp = frontQueue(queue);
          char add = ' ';
          if(input[i+1]!='}')
          {
               //look for the end
               for(;input[i+endP]!='\0';endP++)
               {
                  if(input[i+endP]=='}')
                      break;
               }
               if(input[i+endP]=='\0'&&throwing_INPUT_ERROR())
                    return INPUT_ERROR_DEFINE1;
               //good to go
          }
          else
          {
               //empty set
               add = char(intExpCount);
               //set the this index to be used ... and it is empty.
               enterSet[26+intExpCount][16]=1;
               pushQueue(add, queue);
               intExpCount++;
          }
      }
      i++;
  }
  if(((emptyArr(stack)==false &&topStack(stack)=='('||topStack(stack)==')'))&&(throwing_MISSING_PARENTHESIS()))
  {
       return MISSING_PARENTHESIS1;
  }
  while(!emptyArr(stack))
  {
      char temp = ' ';
      temp = topStack(stack);
      pushQueue(temp, queue);
      popStack(stack);
  }
  RPN = "";
  while(!emptyArr(queue))
  {
      int index = emptyArr(RPN);
      RPN[index]=frontQueue(queue);
      RPN[index+1]='\0';
      popQueue(queue);
  }
  return 0;
}
unsigned int validation(int list[128], char input[], char u[16][10])
{
    unsigned int startP=0, endP=0, startPP=0, endPP=0;
    int i=0;
    if((list[(int)input[i]]==0)&&(throwing_INPUT_ERROR()))
    {
        return INPUT_ERROR_DEFINE1; //return 22
    }
    if(input[i]=='\0'&&throwing_INPUT_EMPTY())
        return INPUT_ERROR_DEFINE1;
    for(unsigned int k = 0; input[k]!='\0'; k++)
    {
      if(list[(int)input[k]]==1 && (int)input[k]>=97 && (int)input[k]<=122)
          input[k]=(int)input[k]-32;
      else if(input[i]=='{')
           startP++;
      else if(input[i]=='}')
           endP++;
      else if(input[i]=='(')
            startPP++;
      else if(input[i]==')')
            startPP--;
    }
    /* no 10 to 6, no 2  no 13, no 4, no 12*/
    unsigned int size = sizeArr(input);
    if(
           list[(int)input[0]]!=1
           ||
           list[(int)input[size-1]]==4
           ||
           list[(int)input[size-1]]==13
           ||
           list[(int)input[size-1]]==12
           ||
           (
               list[(int)input[size-1]]<=10
               &&
               list[(int)input[size-1]]>=6
           )
       )
    {
          throwing_INPUT_ERROR();
          return INPUT_ERROR_DEFINE1;
    }
    else if((list[(int)input[size-1]]==3 || list[(int)input[size-1]]==11)&&
            (
                list[(int)input[size-1]]<=10
                &&
                list[(int)input[size-1]]>=6
            ))
    {
        throwing_INPUT_ERROR();
        return INPUT_ERROR_DEFINE1;
    }
    else if(list[(int)input[size-1]]==4 || list[(int)input[size-1]]==12)
    {
        throwing_INPUT_ERROR();
        return INPUT_ERROR_DEFINE1;
    }
    else if(startP!=endP || startPP!=endPP)
    {
          throwing_MISSING_PARENTHESIS();
          return MISSING_PARENTHESIS1;
    }
    while(input[i]!='\0')
    {
        //if current char is not defined throw error...
        if((list[(int)input[i]]==0)&&(throwing_INPUT_ERROR()))
        {

            return INPUT_ERROR_DEFINE1; //return 2
        }
        //is it variable?
        if(input[i+1]!='\0'&&list[(int)input[i]]==1)
        {
            if(list[(int)input[i+1]]==32 || input[i+1]=='=')
            {
                //may need to upper case the char
            }
            else if(list[(int)input[i+1]]==1)
            {
                 //this is set//this is possbility i shold 0
                 if(input[i]=='S' && i!=0 && throwing_INPUT_EMPTY_NO_SPACE_BEFORE_SET())
                      return INPUT_ERROR_DEFINE1;
                 //this is SET command
                 if(input[i]=='S' && i==0 && input[i+1] =='E' && input[i+2] =='T')
                 {
                       //valid set command with variable (A-Z)
                      if(input[i+3]!=' ' && list[(int)input[i+4]]!=1&&throwing_INPUT_ERROR())
                      {
                            return INPUT_ERROR_DEFINE1;
                      }
                      else
                      {
                          if(list[(int)input[i+5]]==1 && throwing_INPUT_ERROR())
                                return INPUT_ERROR_DEFINE1;
                          //move the index to the variable index
                          subStr(input, 0, 4);
                          i=-1;
                      }

                 }
                 //this is IS command
                 else if(input[i]=='I' && i==0 && input[i+1] =='S')
                 {
                       //valid set command with variable (A-Z)
                      if(input[i+2]!=' ' && list[(int)input[i+3]]!=1 && throwing_INPUT_ERROR())
                      {
                          return INPUT_ERROR_DEFINE1;
                      }
                      else
                      {
                          if(list[(int)input[i+4]]==1 && throwing_INPUT_ERROR())
                                return INPUT_ERROR_DEFINE1;
                          subStr(input, 0, 3);
                          i=-1;

                      }
                 }
                 //color ...
                 else
                 {


                        char tempTEMP[500]={'\0'};
                        unsigned int index = 0;


                        for(unsigned int jj=i; input[jj]!='}' && input[jj]!=',';jj++)
                        {
                            tempTEMP[index]=input[jj];
                            index++;
                        }
                        tempTEMP[index+1]='\0';
                        unsigned int size;
                        bool match=false;
                        for(unsigned int j=0; j<16;j++)
                        {
                            size = sizeArr(u[j]);
                            if(input[i]==u[j][0] && (size ==index))
                            {
                                  unsigned matchChr=0;
                                  for(unsigned int jj=0;jj<size;jj++)
                                  {
                                      if(input[i+jj]==u[j][jj])
                                      {
                                            matchChr++;
                                      }
                                  }
                                  if(matchChr==index)
                                  {
                                       i = subStrInsert(input,i,i+(index), j);
                                       match=true;
                                       j=17;
                                  }

                              }
                        }
                        if(match==false&&throwing_INPUT_ERROR())
                              return INPUT_ERROR_DEFINE1;

                 }

            }
            else
            {
//                cout<<"u here"<<endl;
//                  throwing_INPUT_ERROR();
//                  return INPUT_ERROR_DEFINE1; //return 2
            }
        }
        if(
           (list[(int)input[i]]>=2 && list[(int)input[i]]<=12)
           &&
           (list[(int)input[i+1]]==5)
          )
        {
            unsigned int add = 2;
            for(unsigned int ii=i;input[ii]!='\0';ii++)
            {
                if(input[ii+add]!='\0'&&input[ii+add]==' ')
                {
                    add++;
                      input[ii+1]=input[ii+add];
                }
                else
                    input[ii+1]=input[ii+add];
            }

        }

        if(list[(int)input[i+1]]==2 && list[(int)input[i]]==2)
        {
             throwing_INPUT_ERROR();
             return INPUT_ERROR_DEFINE1; //return 2
        }
        if(
           (list[(int)input[i+1]]==8 ||  list[(int)input[i+1]]==9 || list[(int)input[i+1]]==6)
           &&
           (list[(int)input[i]]==8 ||  list[(int)input[i]]==9 || list[(int)input[i]]==6)
           )
        {
            throwing_INPUT_ERROR();
            return INPUT_ERROR_DEFINE1; //return 2
        }
        i++;

    }
    return PASS;
}
int subStrInsert(char arr[5000], int index, int index1, int replace)
{
    char insert= (replace>=10)?(char)(replace-10+48):(char)(replace+48);
    int returnI = index;
    if(replace>=10)
    {
        arr[index++]=49;
        arr[index++]=insert;
    }
    else
    {
        arr[index]=insert;
        index++;
    }
    while(arr[index1]!='\0')
    {
        arr[index]=arr[index1];
        if(arr[index1+1]=='\0')
        {
            arr[index+1]='\0';
            break;
        }
        else
        {
            arr[index1]='\0';
            index++;
            index1++;
        }
    }
    return (replace>10)?returnI+1:returnI;
}
void subStr(char arr[5000], int index, int index1)
{
    while(arr[index1]!='\0')
    {
        arr[index]=arr[index1];
        if(arr[index1+1]=='\0')
        {
            arr[index+1]='\0';
            break;
        }
        else
        {
            arr[index1]='\0';
            index++;
            index1++;
        }
    }
}
void init(int list[128], char u[16][10])
{
    for(unsigned int i = 0; i<128; list[i]=0, i++);
    list[(int)'<']=14;
    list[(int)'>']=13;
    list[(int)'(']=12;
    list[(int)')']=11;
    list[(int)'~']=10;
    list[(int)'*']=9; //intersection
    list[(int)'+']=8; //union
    list[92]=7; /* 92 = \ char*/
    list[(int)'=']=6;
    list[(int)' ']=5;
    list[(int)'{']=4;
    list[(int)'}']=3;
    list[(int)',']=2;
    for(unsigned int i = 0; i<26; list[(int)'A'+i]=1, list[(int)'a'+i]=1, i++);
    string listU[16]={"WHITE","GOLD","GREY","RED","GREEN","BLUE","ORANGE","PRUPLE","YELLOW","VIOLET","MAGENTA","CYAN","RUST","NAVY","BURGUNDY"
                      ,"BLACK"};
    for(unsigned int i=0;i<16;i++)
    {
        unsigned int limit = listU[i].length();
        for(unsigned int j=0;j<limit;u[i][j]=listU[i][j], j++);
        u[i][limit]='\0';
    }
    //number 13 for digit 0 to 9
    for(unsigned int i=48;i<58;i++)
    {
        list[i]=15;
    }
}
void show(unsigned int enterSet[52][16], char u[16][10])
{
    for(unsigned int i =0, index = 65; i<26;++i, ++index)
    {
         std::cout<<"->"<<(char)index<<" = {";
         bool empty = true;
         for(unsigned int j = 0; j<16;++j)
         {
            if(empty==true&& enterSet[i][j]==1)
                empty=false;
            if(enterSet[i][j]==1)
              std::cout<<u[j]<<",";
          }
          if(empty==false)
              std::cout<<"\b";
          std::cout<<"}"<<std::endl;
          if(i==25 && index == 90)
          {
              i=0;
              index = 97;
          }
    }
}
bool throwing_INPUT_EMPTY_NO_SPACE_BEFORE_SET()
{
    std::cout<<"Error: No space before key word -- SET."<<std::endl;
    return true;
}
bool throwing_INPUT_EMPTY()
{
    std::cout<<"Error: No input."<<std::endl;
    return true;
}
bool throwing_INPUT_ERROR()
{
    std::cout<<"Error: Incorrect input."<<std::endl;
    return true;
}
bool throwing_MISSING_PARENTHESIS()
{
    std::cout<<"Error: Missing Parenthesis, here"<<std::endl;
    return true;
}
bool throwing_UNKNOW_ERROR()
{
    std::cout<<"Error"<<std::endl;
    return true;
}
bool throwing_NO_MEMORY_ERROR()
{
    std::cout<<"No memory stored by this index"<<std::endl;
    return true;
}
bool throwing_need_space_ERROR()
{
    std::cout<<"Error Input: Need space between command and expression."<<std::endl;
    return true;
}
