#include<iostream>
#include<stdio.h>
#include<vector>
std::vector<int> ar;
using namespace std;
int cnt=0;
void update(int a[][1000],int row1,int row2,int col1,int col2)
{
    int i=0,j=0;
    for(i=row1;i<=row2;i++)
        for(j=col1;j<=col2;j++)
            a[i][j]=-1;
}

int satisfyl(int a[][1000],int row1,int row2,int col1,int col2,int l,int row,int col)
{
    if(row1<0||row2<0||col1<0||col2<0||row1>=row||row2>=row||col1>=col||col2>=col)
      return 0;
    //return 1;
    int count1=0 , count0=0,i,j;
    for(i=row1;i<=row2;i++)
    {
        for(j=col1;j<=col2;j++)
        {
            if(a[i][j]==0)
                count0++;
            else
                count1++;
        }
    }
    if(count1>=l&&count0>=l)
        return 1;
    else
        return 0;

}

int satisfyH(int a[][1000],int row1,int row2,int col1,int col2,int h,int row,int col)
{
  //return 1;
  if(row1<0||row2<0||col1<0||col2<0||row1>=row||row2>=row||col1>=col||col2>=col)
      return 0;
  int i,j;
  for(i=row1;i<=row2;i++)
  {
      for(j=col1;j<=col2;j++)
      {
          if(a[i][j]==-1)
            return 0;
      }
  }
  int k1=row2-row1;
  int k2=col1-col2;
  if(k1<0)
    k1=-k1;
  if(k2<0)
    k2=-k2;
  int k=(k1+1)*(k2+1);
  if(k<=h)
      return 1;
  else
      return 0;
}

int *enlarge(int *br,int row1,int row2,int col1,int col2,int direction)
{
    int newr[2],newc[2];
    newr[0]=row1;
    newr[1]=row2;
    newc[0]=col1;
    newc[1]=col2;
    int *b;

    int newdir;
    if(direction==0)
    {
        newc[1]+=1;
        newdir=1;
    }
    if(direction==1)
    {
        newr[1]+=1;
        newdir=2;
    }
    if(direction==2)
    {
        newc[0]-=1;
        newdir=3;
    }
    if(direction==3)
    {
        newr[0]-=1;
        newdir=0;
    }
    br[0]=newr[0];
    br[1]=newr[1];
    br[2]=newc[0];
    br[3]=newc[1];
    br[4]=newdir;
    //cout<<br[0]<<endl;
    return br;
}

int *newrect(int *w,int a[][1000],int row,int col,int H,int L,int row_m,int col_m)
{
    int *we,*b;
    int r_end[2],c_end[2];
    //cout<<row<<col;
    r_end[0]=row,
    r_end[1]=row;
    c_end[0]=col;
    c_end[1]=col;
    //cout<<r_end[0]<<r_end[1];
    int direction = 0;
    int out = 0,legal,counter=0;
    while(!out)
    {
        legal =0;
        counter=0;
        while(counter<3)
        {
            int br[5];
            b=enlarge(br,r_end[0],r_end[1],c_end[0],c_end[1],direction);
            direction=b[4];
            //legal=1;
            //break;
            //cout<<"b "<<r_end[0]<<" "<<c_end[1]<<endl;
            if(satisfyH( a ,b[0] , b[1] , b[2] , b[3] , H , row_m , col_m ))
            {
                legal=1;
                r_end[0]=b[0];
                r_end[1]=b[1];
                c_end[0]=b[2];
                c_end[1]=b[3];
                break;
            }
            counter+=1;
        }
        if(!legal)
            out=1;

    }
    //cout<<r_end[0]<<" "<<c_end[0]<<" "<<c_end[1]<<endl;
    int success = satisfyl(a,r_end[0],r_end[1],c_end[0],c_end[1],L,row_m,col_m);
        w[0] = success;
        w[1]=r_end[0];
        w[2]=r_end[1];
        w[3]=c_end[0];
        w[4]=c_end[1];
//         cout<<"newrect"<<" "<<w[0]<<endl;

        //cout<<endl;
        return w;
}

void start(int a[][1000],int row,int col,int H,int L)
{
    int i,j;
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            int *b;
            int w[5];
            b = newrect(w,a,i,j,H,L,row,col);
            if(b[0]==1)
            {
                //printf("yes");
                ar.push_back(b[1]);
                ar.push_back(b[2]);
                ar.push_back(b[3]);
                ar.push_back(b[4]);
                cout<<b[1]<<" "<<b[3]<<" "<<b[2]<<" "<<b[4]<<endl;
                cnt++;
                update(a,b[1],b[2],b[3],b[4]);
            }
        }
    }
    for(i=0;i<row;i++)
    {
        for(j=0;j<col;j++)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<endl;
    }
}
typedef long long int ll;
int main()
{
int row,col,min,max,i,j;
cin>>row>>col>>min>>max;
int a[row][1000];
string ch;
ll k=0;
for(i=0;i<row;i++)
{
    cin>>ch;
    for(j=0;j<col;j++)
    {
    if(ch[k]=='T')
        a[i][j]=0;
    else
        a[i][j]=1;
        k++;
    }
}
/*for(i=0;i<row;i++)
{
    for(j=0;j<col;j++)
    {
       cout<<a[i][j]<<" ";
    }
    cout<<endl;
}
*/
start(a,row,col,max,min);
//cout<<ar.empty();
//cout<<cnt;
return 0;
}
