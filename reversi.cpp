#include <iostream>  
#include <fstream>  
#include <string>  
#include <queue> 
#include <sstream>
#include <vector>
using namespace std;
struct compare
{
	bool operator()(const int& l, const int& r)
	{
		return l > r;
	}
};
static stringstream  min_max_log;
static stringstream  a_b_log;
static int a_b_best_step=-1;
static char player;
static	int location=-1;
int min_value(char **board,char cur_player,int cut_off_depth,int depth,int location,int alpha,int beta,int pass,int isend);
void show_board(char **board)
{
	for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				
				cout << board[i][j];
			}
			cout << endl;
		}
}
bool same_color(char **board)
{   
	int count_x=0;
	int count_o=0;
	for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				
				if(board[i][j]=='X')count_x++;
				if(board[i][j]=='O')count_o++;
				
			}
			
		}
		if(count_x==0||count_o==0) return true;
		else return false;
}

vector<int> next_step(char **board, char cur_player)
{
	int i;
	int j;
	int m[88];
    for(i=0;i<88;i++)m[i]=0;
	vector<int> v;
	for (i = 0; i<8; i++)
	{
		for (j = 0; j<8; j++)
		{
			if (board[i][j] == cur_player)
			{   //up
			    if(i!=0)
			    {
			    		if(board[i-1][j]!=cur_player&&board[i-1][j]!='*')
					{
						int p = i - 1;
				    	int q = j;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p--;

							}

					
						}
					
					}
			    }
				
				

			
				//down
			    if(i!=7)
			    {
			    		if(board[i+1][j]!=cur_player&&board[i+1][j]!='*')
					{
						int p = i + 1;
				    	int q = j;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
								if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p++;

							}

					
						}
					
					}
			    }
				//left
			    if(j!=0)
			    {
			    		if(board[i][j-1]!=cur_player&&board[i][j-1]!='*')
					{
						int p = i;
				    	int q = j-1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
								if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								//	cout<<p<<q;
								}
								break;
							}
							else
							{
								q--;

							}

					
						}
					
					}
			    }
				//right
			    if(j!=7)
			    {
			    		if(board[i][j+1]!=cur_player&&board[i][j+1]!='*')
					{
						int p = i;
				    	int q = j+1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
								if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								q++;

							}

					
						}
					
					}
			    }
				//upleft
				if(i!=0&&j!=0)
			    {
			    		if(board[i-1][j-1]!=cur_player&&board[i-1][j-1]!='*')
					{
						int p = i - 1;
				    	int q = j-1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
								if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p--;
								q--;

							}

					
						}
					
					}
			    }
				//upright
				if(i!=0&&j!=7)
			    {
			    		if(board[i-1][j+1]!=cur_player&&board[i-1][j+1]!='*')
					{
						int p = i - 1;
				    	int q = j+1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
								if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p--;
								q++;

							}

					
						}
					
					}
			    }
				//downleft
				if(i!=7&&j!=0)
			    {
			    		if(board[i+1][j-1]!=cur_player&&board[i+1][j-1]!='*')
					{
						int p = i + 1;
				    	int q = j - 1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p++;
								q--;

							}

					
						}
					
					}
			    }
				//downright
				if(i!=7&&j!=7)
			    {
			    		if(board[i+1][j+1]!=cur_player&&board[i+1][j+1]!='*')
					{
						int p = i + 1;
				    	int q = j + 1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]==cur_player) break;
							if (board[p][q] == '*')
							{
								if (m[p * 10 + q] != 1)
								{
									v.push_back(p*10+q);
									m[p * 10 + q] = 1;
								}
								break;
							}
							else
							{
								p++;
								q++;

							}

					
						}
					
					}
			    }
				
			}

		}

	}
	return v;

}


int evaluate(char **board,char cur_player)
{
int w[8][8]={{99,-8,8,6,6,8,-8,99},{-8,-24,-4,-3,-3,-4,-24,-8},{8,-4,7,4,4,7,-4,8},{6,-3,4,0,0,4,-3,6},{6,-3,4,0,0,4,-3,6},{8,-4,7,4,4,7,-4,8},{-8,-24,-4,-3,-3,-4,-24,-8},{99,-8,8,6,6,8,-8,99}};
	int weight_ply=0;
	int weight_opp=0;
	int i;
	int j;
	for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				if(board[i][j] !='*')
				{
					if(board[i][j]==cur_player)
					weight_ply+=w[i][j];
					else
					weight_opp+=w[i][j];
				}
				
	   		
			}
		
		}
		return weight_ply-weight_opp;
}

void flipboard(char **board,char cur_player,int position)
{
	int i=position/10;
	int j=position%10;
	board[i][j]=cur_player;
	vector<int> v;
	 //up
			    if(i!=0)
			    {
			    		if(board[i-1][j]!=cur_player&&board[i-1][j]!='*')
					{
						int p = i - 1;
				    	int q = j;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								p--;
								

							}

					
						}
					
					}
			    }
			    v.clear();
	 //down
			    if(i!=7)
			    {		
			    		if(board[i+1][j]!=cur_player&&board[i+1][j]!='*')
					{
						int p = i + 1;
				    	int q = j;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{	
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
									
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
							//	cout<<"p"<<"q"<<p<<q<<endl;
								p++;
								

							}

					
						}
					
					}
			    }
			    v.clear();
	 //left
			    if(j!=0)
			    {
			    		if(board[i][j-1]!=cur_player&&board[i][j-1]!='*')
					{
						int p = i ;
				    	int q = j-1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								q--;
								

							}

					
						}
					
					}
			    }
			    v.clear(); 
	//right
			    if(j!=7)
			    {
			    		if(board[i][j+1]!=cur_player&&board[i][j+1]!='*')
					{
						int p = i ;
				    	int q = j + 1 ;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								q++;
								

							}

					
						}
					
					}
			    }
			    v.clear();
	 //upleft
			    if(i!=0&&j!=0)
			    {
			    		if(board[i-1][j-1]!=cur_player&&board[i-1][j-1]!='*')
					{
						int p = i - 1;
				    	int q = j-1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								p--;
								q--;
								

							}

					
						}
					
					}
			    }
			    v.clear();
	//upright
			    if(i!=0&&j!=7)
			    {
			    		if(board[i-1][j+1]!=cur_player&&board[i-1][j+1]!='*')
					{
						int p = i-1 ;
				    	int q = j+1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								p--;
								q++;
								

							}

					
						}
					
					}
			    }
			    v.clear(); 
	 //downleft
			    if(i!=7&&j!=0)
			    {
			    		if(board[i+1][j-1]!=cur_player&&board[i+1][j-1]!='*')
					{
						int p = i + 1;
				    	int q = j-1;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								p++;
								q--;
								

							}

					
						}
					
					}
			    }
			    v.clear();
	 
	//downright
			    if(i!=7&&j!=7)
			    {
			    		if(board[i+1][j+1]!=cur_player&&board[i+1][j+1]!='*')
					{
						int p = i+1 ;
				    	int q = j + 1 ;
				    	while (p >= 0 && q >= 0&&p<=7&&q<=7)
						{
							if(board[p][q]=='*') break;
							if (board[p][q] == cur_player)
							{
								for(int v_length=0;v_length<v.size();v_length++)
								{
									board[v.at(v_length)/10][v.at(v_length)%10]=cur_player;
								}
								
								break;
							}
							else
							{
								v.push_back(p*10+q);
								p++;
								q++;
								

							}

					
						}
					
					}
			    }
			    v.clear();
}

vector<int> change_order(vector<int> v)
{   int i;
	priority_queue<int,vector<int>,compare > pq;
	int v_size=v.size();
    for(i=0;i<v_size;i++)
    {
    	pq.push(v.at(i));
    }
    v.clear();
    for(i=0;i<v_size;i++)
    {
    	v.push_back(pq.top());
    	pq.pop();
   }
   return v;
}
void greedy(char **board, char cur_player)
{   int i;

    int max_w=-100000;
    int location=0;
    
	char **new_board;
	new_board = new char *[8];
	for (i = 0; i < 8; i++)
		{
			new_board[i] = new char[8];
		}
    vector<int> v = next_step(board, cur_player);
    v=change_order(v);
   
   
	for( i=0;i<v.size();i++)
	{
	//	cout << v.at(i) << endl;
		
		for(int p=0;p<8;p++)
		{
			for(int q=0;q<8;q++)
			{
				new_board[p][q]=board[p][q];
			}
		}
		flipboard(new_board,cur_player,v.at(i));
		if(max_w<evaluate(new_board,cur_player)) 
		{
			max_w=evaluate(new_board,cur_player); location=v.at(i);
		}
		//cout<<evaluate(new_board,cur_player)<<endl;
	
		
	}
	if(v.size()!=0)	flipboard(board,cur_player,location);
	//	show_board(board);
		ofstream fileStream("output.txt", ios_base::out);
	if (!fileStream)
	{
		cout << "fail" << endl;
	}
	else
	{
		for(int m=0;m<8;m++)
		{
			for(int n=0;n<8;n++)
			{
				fileStream << board[m][n]  ;
			}
			fileStream<<endl;
		}
		
	}
	fileStream.close();
		cout<<"Max_Weight:"<<max_w<<endl;
		cout<<"Location"<<location/10<<" "<<location%10<<endl;
	
	
      	
		

	
	
}

int find_max_min(char **board,char cur_player,int cut_off_depth,int option,int l,int depth,int pass)
{   char name[8]={'a','b','c','d','e','f','g','h'};
	int i;
    int min=100000;
	int max=-100000; 
	char opp_player;

	vector<int> res;
	if(cur_player=='X') opp_player='O';
	else opp_player='X';
//	cout<<cur_player;
//	cout<<opp_player<<"aaa"<<endl;
	char **new_board;
	new_board = new char *[8];
	for (i = 0; i < 8; i++)
		{
			new_board[i] = new char[8];
		}
	int evaluation=evaluate(board,player);
	vector<int> v = next_step(board, cur_player);
	v=change_order(v);	
	
if(l==25&&cut_off_depth==1)
//	show_board(board);
{
cout<<"vector:";
	for(i=0;i<v.size();i++) {
	cout<<v.at(i);int test=v.at(i);}
	cout<<endl;

}
	vector<int> w = next_step(board, opp_player);

if(pass==2)
{
	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
	return evaluation;
}

if(v.size()==0&&w.size()==0&&same_color(board)==true)
{
	if(depth-cut_off_depth==0)
	{
		min_max_log<<"root"<<','<<0<<','<<evaluation<<'\n';		
	}
	else
	{
		min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
	}
	return evaluation;
}
else
{   
	if(option==1)
	{
		if(pass==1)
		{			
			if(cut_off_depth==0)  
			{   
				min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
				return evaluation;
			}
			if(max==-100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
				else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<max<<'\n';		 
    		
			if(v.size()==0)
			{
				int temp_max=find_max_min(board,opp_player,cut_off_depth-1,0,l,depth,2);
				if(max<temp_max) 
				{
					max=temp_max;
				}
				if(max==-100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
				else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<max<<'\n';		       
			}
			else 
			{
					for( i=0;i<v.size();i++)
					{   
		    			for(int p=0;p<8;p++)
						{
							for(int q=0;q<8;q++)
							{
								new_board[p][q]=board[p][q];
							}
						}
						flipboard(new_board,cur_player,v.at(i));
																								
						int temp_max=find_max_min(new_board,opp_player,cut_off_depth-1,0,v.at(i),depth,0);
						if(max<temp_max) 
						{
							max=temp_max;
							if(cut_off_depth==depth)location=v.at(i);
						}
						if(max==-100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
						else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<max<<'\n';	
				
					}
			}
		}
		else
		{   
			if(cut_off_depth==0)  
			{   
				min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
				return evaluation;
			}
			if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<max<<endl;
					if(max==-100000) min_max_log<<"root"<<','<<0<<','<<"-Infinity"<<'\n';
					else min_max_log<<"root"<<','<<0<<','<<max<<'\n';
				}
		    else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(max==-100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<'\n';
		        }
		    if(v.size()==0)
			{
				int temp_max=find_max_min(board,opp_player,cut_off_depth-1,0,l,depth,1);
				if(max<temp_max) 
				{
					max=temp_max;
				}
			if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<max<<endl;
					if(max==-100000) min_max_log<<"root"<<','<<0<<','<<"-Infinity"<<'\n';
					else min_max_log<<"root"<<','<<0<<','<<max<<'\n';
				}
		    else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(max==-100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<'\n';
		        }    
			}
			else 
			{
					for( i=0;i<v.size();i++)
					{   
		    			for(int p=0;p<8;p++)
						{
							for(int q=0;q<8;q++)
							{
								new_board[p][q]=board[p][q];
							}
						}
						flipboard(new_board,cur_player,v.at(i));
				
						int temp_max=find_max_min(new_board,opp_player,cut_off_depth-1,0,v.at(i),depth,0);
						if(max<temp_max) 
						{
							max=temp_max;
						if(cut_off_depth==depth)location=v.at(i);
						}
					if(depth-cut_off_depth==0)
					{
						//	cout<<"root"<<','<<0<<','<<max<<endl;
						if(max==-100000) min_max_log<<"root"<<','<<0<<','<<"-Infinity"<<'\n';
						else min_max_log<<"root"<<','<<0<<','<<max<<'\n';
					}
		   			 else
					{
					//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(max==-100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<'\n';
		        	}    
				
					}
			}
		}
		return max;
	}
	else
	{
		if(pass==1)
		{		
			if(cut_off_depth==0)  
			{   
				min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
				return evaluation;
			}		
			if(min==100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
			else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<min<<'\n';		 	
			if(v.size()==0)
			{
				int temp_min=find_max_min(board,opp_player,cut_off_depth-1,1,l,depth,2);
				if(min>temp_min) 
				{
					min=temp_min;
				
				}
				if(min==100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
				else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<min<<'\n';		       
			}
			else 
			{
					for( i=0;i<v.size();i++)
					{   
		    			for(int p=0;p<8;p++)
						{
							for(int q=0;q<8;q++)
							{
								new_board[p][q]=board[p][q];
							}
						}
						flipboard(new_board,cur_player,v.at(i));
				
						int temp_min=find_max_min(new_board,opp_player,cut_off_depth-1,1,v.at(i),depth,0);
						if(min>temp_min) 
						{
							min=temp_min;
						}
						if(min==100000)	min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
						else min_max_log<<"pass"<<','<<depth-cut_off_depth<<','<<min<<'\n';	
				
					}
			}
		}
		else
		{	
			if(cut_off_depth==0)  
			{   
				min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
				return evaluation;
			}
			if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<max<<endl;
					if(min==100000) min_max_log<<"root"<<','<<0<<','<<"Infinity"<<'\n';
					else min_max_log<<"root"<<','<<0<<','<<min<<'\n';
				}
		    else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(min==100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<'\n';
		        }
		    if(v.size()==0)
			{
				int temp_min=find_max_min(board,opp_player,cut_off_depth-1,1,l,depth,1);
				if(min>temp_min) 
				{
					min=temp_min;
				
				}
				if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<max<<endl;
					if(min==100000) min_max_log<<"root"<<','<<0<<','<<"Infinity"<<'\n';
					else min_max_log<<"root"<<','<<0<<','<<min<<'\n';
				}
		    else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(min==100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<'\n';
		        }
			}
			else 
			{
					for( i=0;i<v.size();i++)
					{   
		    			for(int p=0;p<8;p++)
						{
							for(int q=0;q<8;q++)
							{
								new_board[p][q]=board[p][q];
							}
						}
						flipboard(new_board,cur_player,v.at(i));
				      
						int temp_min=find_max_min(new_board,opp_player,cut_off_depth-1,1,v.at(i),depth,0);
						if(min>temp_min) 
						{
							min=temp_min;
						}
						if(depth-cut_off_depth==0)
						{
						//	cout<<"root"<<','<<0<<','<<max<<endl;
						if(min==100000) min_max_log<<"root"<<','<<0<<','<<"Infinity"<<'\n';
						else min_max_log<<"root"<<','<<0<<','<<min<<'\n';
						}
		    			else
						{
						//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(min==100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<'\n';
		        		}
				
					}
			}
		}
		return min;
	}
}
/*	if(cut_off_depth==0)  
	{   int evaluation=evaluate(board,cur_player);
		cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<endl;
		min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<'\n';
		res.push_back(evaluation) ;
		return res;
	}
	else
	{
		vector<int> v = next_step(board, cur_player);
		v=change_order(v);
		if(option==1)
		{   if(depth-cut_off_depth==0)
			{
			//	cout<<"root"<<','<<0<<','<<max<<endl;
				if(max==-100000) min_max_log<<"root"<<','<<0<<','<<"-Infinity"<<'\n';
				else min_max_log<<"root"<<','<<0<<','<<max<<'\n';
			}
		    else
		//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
			if(max==-100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
			else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<'\n';
			for( i=0;i<v.size();i++)
			{   
		    	for(int p=0;p<8;p++)
				{
					for(int q=0;q<8;q++)
					{
						new_board[p][q]=board[p][q];
					}
				}
				flipboard(new_board,cur_player,v.at(i));
				
				int temp_max=find_max_min(new_board,opp_player,cut_off_depth-1,0,v.at(i),depth).at(0);
				if(max<temp_max) 
				{
					max=temp_max;
					location=v.at(i);
				}
				if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<max<<endl;
					if(max==-100000) min_max_log<<"root"<<','<<0<<','<<"-Infinity"<<'\n';
					else min_max_log<<"root"<<','<<0<<','<<max<<'\n';
				}
		        else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<endl;
						if(max==-100000)	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"-Infinity"<<'\n';
						else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<max<<'\n';
		        }
				
			}
			
			res.push_back(max);
			res.push_back(location);
		}
		
		else
		{   if(depth-cut_off_depth==0)
			{
			//	cout<<"root"<<','<<0<<','<<min<<endl;
				if(min==100000) min_max_log<<"root"<<','<<0<<','<<"Infinity"<<'\n';
				else min_max_log<<"root"<<','<<0<<','<<min<<'\n';
			}
		    else
		//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<endl;
			if(min==100000) min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
			else min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<'\n';
			for( i=0;i<v.size();i++)
			{
				for(int p=0;p<8;p++)
				{
					for(int q=0;q<8;q++)
					{
						new_board[p][q]=board[p][q];
					}
				}
				flipboard(new_board,cur_player,v.at(i));
				
				int temp_min=find_max_min(new_board,opp_player,cut_off_depth-1,1,v.at(i),depth).at(0);
				if(min>temp_min) 
				{
					min=temp_min;
					location=v.at(i);
				}
				if(depth-cut_off_depth==0)
				{
				//	cout<<"root"<<','<<0<<','<<min<<endl;
					if(min==100000) min_max_log<<"root"<<','<<0<<','<<"Infinity"<<'\n';
				else min_max_log<<"root"<<','<<0<<','<<min<<'\n';
				}
		        else
				{
				//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<endl;
					if(min==100000)		min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<"Infinity"<<'\n';
					else	min_max_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<min<<'\n';
				}
				
				
			}
				res.push_back(min);
			res.push_back(location);
		}
		return res;
		
	}*/
}
void min_max(char **board, char cur_player, int cut_off_depth,int option)
{   

   int max_value=	find_max_min(board,cur_player,cut_off_depth,1,-1,cut_off_depth,0);
	if(location!=-1)	flipboard(board,cur_player,location);
	show_board(board);
		ofstream fileStream("output.txt", ios_base::out);
	if (!fileStream)
	{
		cout << "fail" << endl;
	}
	else
	{
		for(int m=0;m<8;m++)
		{
			for(int n=0;n<8;n++)
			{
				fileStream << board[m][n]  ;
			}
			fileStream<<endl;
		}
		fileStream<<"Node,Depth,Value"<<endl;
		fileStream<<min_max_log.str()<<endl;
	}
	fileStream.close();
	//cout<<min_max_log.str()<<endl;
	cout<<"Max:"<<max_value<<endl;
	cout<<"Location:"<<location<<endl;
	
	
}


int max_value(char **board,char cur_player,int cut_off_depth,int depth,int l,int alpha,int beta,int pass,int isend)
{       char name[8]={'a','b','c','d','e','f','g','h'};
		int i;
		char opp_player;
		if(cur_player=='X') {
		opp_player='O';}
	    else opp_player='X';
	    int test1=cur_player;
	    int test2='X';
	    cout<<"test"<<test1<<test2;
    	char **new_board;
		new_board = new char *[8];
		for (i = 0; i < 8; i++)
		{
			new_board[i] = new char[8];
		}
   		int evaluation=evaluate(board,player); 	
				int temp = -10000;
				string temp_string = "-Infinity";
			//	show_board(board);
			//		cout<<"cur_player"<<cur_player<<endl;

	   		//	cout<<"opp_player"<<opp_player<<endl;
	  			vector<int> v = next_step(board, cur_player);
	  				for(i=0;i<v.size();i++) cout<<name[v.at(i)%10]<<v.at(i)/10+1;
	   			cout<<endl;
	   			v=change_order(v);
	   				for(i=0;i<v.size();i++) cout<<name[v.at(i)%10]<<v.at(i)/10+1;
	   			cout<<endl;
	   		//	cout<<"cur_player"<<cur_player<<endl;
	   		//	cout<<"opp_player"<<opp_player<<endl;
				vector<int> w = next_step(board, opp_player);
	   		
	   //			if(pass==1&&v.size()==0)
	   	//	{
	   	//			if(alpha==-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<"Infinity"<<'\n';
		//			if(alpha==-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<beta<<'\n';
		//			if(alpha!=-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<"Infinity"<<'\n';
		//			if(alpha!=-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<'\n';
		//			temp = min_value(board, opp_player, cut_off_depth - 1, depth, l, alpha, beta, 1);

		//			return evaluation;
	   //		}
	   	//		else
		//		   {
				if (pass==2)
				{
					
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << alpha << ',' << beta << '\n';




					
					return evaluation;
				}
				if (v.size() == 0 && w.size()==0&&same_color(board)==true)
				{
					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << alpha << ',' << beta << '\n';




					}
					else{
						if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << alpha << ',' << beta << '\n';
					}
					return evaluation;
				}
				
	   			if(pass==1)
	   			{
	   				
							if(depth-cut_off_depth==0)
						{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
			
		    				else
						//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
	   					{
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						
					
					
	   			}
	   			else
			 {
	   			
			 	  	
			 	  		if(cut_off_depth==0)  
					{   
						//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<endl;
						if(alpha==-10000&&beta==10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<"Infinity"<<'\n';
						if(alpha==-10000&&beta!=10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<beta<<'\n';
						if(alpha!=-10000&&beta==10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<"Infinity"<<'\n';
						if(alpha!=-10000&&beta!=10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<'\n';
						return evaluation;
					}
	   	
	   					if(depth-cut_off_depth==0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
			
					 else
					//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
	   				{
						 if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						 if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						 if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						 if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
	   
			}
			if(v.size()==0)
			{
				if (pass == 1)
				{
					temp = min_value(board, opp_player, cut_off_depth - 1, depth, l, alpha, beta, 2, 1);
					if(temp!=-10000)
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}
					
				}
				else
				{
					temp = min_value(board, opp_player, cut_off_depth - 1, depth, l, alpha, beta, 1, 0);
						if(temp!=-10000)
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}
				}
				if (temp >= beta)
				{
					if (pass == 1)
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}

						else
							//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						{
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					else
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						else
						{
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					return temp;
				}
				if(alpha<temp)
				{					
					if(depth-cut_off_depth==0)
					{
						a_b_best_step=-1;
					}			
							alpha=temp;
				}
			
			   if(pass==1)
			   {
			   			if(depth-cut_off_depth==0)
						{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
			
		    				else
						//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
	   					{
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
			   }	
				else
				{
				if(depth-cut_off_depth==0)
				{
					//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
					if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
					if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
					if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
					if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
				}
		        else
				{	
					//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
					if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
					if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
					if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
					if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
				}	
				}
				return temp;
							
			}
			else
			{
				
			
			for( i=0;i<v.size();i++)
			{   
		    	for(int p=0;p<8;p++)
				{
					for(int q=0;q<8;q++)
					{
						new_board[p][q]=board[p][q];
					}
				}
				flipboard(new_board,cur_player,v.at(i));
				
				
				temp=max(temp,min_value(new_board,opp_player,cut_off_depth-1,depth,v.at(i),alpha,beta,0,0));
				if (temp != -10000) 
					if(temp!=-10000)
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}
				 if (temp >= beta)
				 {
					 
					 if (pass == 1)
					 {
						 if (depth - cut_off_depth == 0)
						 {
							 //cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							 if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							 if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							 if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							 if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						 }

						 else
							 //	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						 {
							 if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							 if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							 if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							 if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						 }
					 }
					 else{

						 if (depth - cut_off_depth == 0)
						 {
							 //cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							 if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							 if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							 if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							 if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						 }
						 else
						 {
							 //cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							 if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							 if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							 if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							 if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						 }
					 }
					 
					 return temp;


				 }
				if(alpha<temp)
				{
						if(depth-cut_off_depth==0)
					{
						a_b_best_step=v.at(i);
					}
					alpha=temp;
				}
				if (pass == 1)
				{
					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}

					else
						//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
					{
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
				}
				else{

					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
					else
					{
						//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
				}
			
				
			}
			return temp;
			}
	   	
	//  }
	   
			
		
	 
	   
   
   }
int min_value(char **board,char cur_player,int cut_off_depth,int depth,int l,int alpha,int beta,int pass,int isend)
{		char name[8]={'a','b','c','d','e','f','g','h'};
		int i;
     	char opp_player;
		if(cur_player=='X') opp_player='O';
	    else opp_player='X';
	    
    	char **new_board;
		new_board = new char *[8];
		for (i = 0; i < 8; i++)
		{
			new_board[i] = new char[8];
		}
   	int evaluation=evaluate(board,player);
   //	if(pass==1&&cut_off_depth==0)evaluation=-evaluation;
   	if(false) return evaluation;
   	else
	{
				int temp = 10000;
				string temp_string="Infinity";

	   			vector<int> v = next_step(board, cur_player);
	   			v=change_order(v);
				vector<int> w = next_step(board, opp_player);
				
	   			for(i=0;i<v.size();i++) cout<<name[v.at(i)%10]<<v.at(i)/10+1;
	   			cout<<endl;
	   	//		if(pass==1&&v.size()==0)
	   	//		{
	   	//			if(alpha==-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<"Infinity"<<'\n';
		//			if(alpha==-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<beta<<'\n';
		//			if(alpha!=-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<"Infinity"<<'\n';
		//			if(alpha!=-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<'\n';
		//			return evaluation;
	   	//		}
	   			//else
				  // {
					if (pass==2)
				{
					
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth-cut_off_depth << ',' << evaluation << ',' << alpha << ',' << beta << '\n';




					
					return evaluation;
				}
				if (v.size()==0&&w.size()==0&&same_color(board)==true)
				{
					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << evaluation << ',' << alpha << ',' << beta << '\n';




					}
					else{
						if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << evaluation << ',' << alpha << ',' << beta << '\n';
					}return evaluation;
				}
	   			if(pass==1)
	   			{
	   				if(cut_off_depth==0)  
					{   
					//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<endl;
					if(alpha==-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<"Infinity"<<'\n';
					if(alpha==-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<beta<<'\n';
					if(alpha!=-10000&&beta==10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<"Infinity"<<'\n';
					if(alpha!=-10000&&beta!=10000)	a_b_log<<"pass"<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<'\n';
					return evaluation;
					}
					else
					{
							if(depth-cut_off_depth==0)
						{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
			
		    				else
						//	cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
	   					{
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						
					}
	   			}
	  	else{
	  		 
	   if(cut_off_depth==0)  
			{   
				//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<endl;
				if(alpha==-10000&&beta==10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<"Infinity"<<'\n';
				if(alpha==-10000&&beta!=10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<"-Infinity"<<','<<beta<<'\n';
				if(alpha!=-10000&&beta==10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<"Infinity"<<'\n';
				if(alpha!=-10000&&beta!=10000)	a_b_log<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<evaluation<<','<<alpha<<','<<beta<<'\n';
				return evaluation;
			}
	   		
	   			if(depth-cut_off_depth==0)
			   {
			   		//cout<<"root"<<','<<0<<','<<beta<<','<<alpha<<','<<beta<<endl;
					if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
					if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
					if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
					if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
			   }
		    else
		    {
		    		//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<beta<<','<<alpha<<','<<beta<<endl;
				if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
				if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
				if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string<< ',' << alpha << ',' << "Infinity" << '\n';
				if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
		    }
		}
	   	
	   	if(v.size()==0)
		{
			if (pass==1)
	   		{
	   			 temp=max_value(board,opp_player,cut_off_depth-1,depth,l,alpha,beta,2,1);
	   			 if(temp!=10000)
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}
	
			}
			else 
			{temp = max_value(board, opp_player, cut_off_depth - 1, depth, l, alpha, beta, 1, 0);
			if(temp!=10000)
					
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}	
			}
				if (temp <= alpha)
				{	
					if (pass == 1)
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						else
						{
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					else
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<beta<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						else
						{
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<beta<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					return temp;
				}
							if(beta>temp)
						{							
							beta=temp;
						}
				if(pass==1)		
						{
							if(depth-cut_off_depth==0)
							{
							//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
							}
		        			else
							{	
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
							}
						}	
				else
				{
							if(depth-cut_off_depth==0)
			   				{
			   				//cout<<"root"<<','<<0<<','<<beta<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
			   				}
		    				else
		   		 			{
		    				//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<beta<<','<<alpha<<','<<beta<<endl;
								if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
								if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
								if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
								if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
		    				}
				}
				return temp;
					
	   	}
		else{
			
			
	   		for( i=0;i<v.size();i++)
			{   
		    	for(int p=0;p<8;p++)
				{
					for(int q=0;q<8;q++)
					{
						new_board[p][q]=board[p][q];
					}
				}
				flipboard(new_board,cur_player,v.at(i));
				
				temp=min(max_value(new_board,opp_player,cut_off_depth-1,depth,v.at(i),alpha,beta,0,0),temp);
					if(temp!=10000)
					{	ostringstream ss;
						ss<<temp;
						temp_string = ss.str();
					}
				
				if (temp <= alpha)
				{	
					if (pass == 1)
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						else
						{
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					else
					{
						if (depth - cut_off_depth == 0)
						{
							//cout<<"root"<<','<<0<<','<<beta<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
						else
						{
							//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<beta<<','<<alpha<<','<<beta<<endl;
							if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
							if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
							if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
							if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
						}
					}
					return temp;
				}
				beta = min(beta, temp);
				
				if (pass == 1)
				{
					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
					else
					{
						//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<alpha<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "pass" << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
				}
				else
				{
					if (depth - cut_off_depth == 0)
					{
						//cout<<"root"<<','<<0<<','<<beta<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << "root" << ',' << 0 << ',' << temp_string << ',' << alpha << ',' << beta << '\n';
					}
					else
					{
						//cout<<name[l%10]<<l/10+1<<','<<depth-cut_off_depth<<','<<beta<<','<<alpha<<','<<beta<<endl;
						if (alpha == -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << "-Infinity" << ',' << "Infinity" << '\n';
						if (alpha == -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' <<temp_string << ',' << "-Infinity" << ',' << beta << '\n';
						if (alpha != -10000 && beta == 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string << ',' << alpha << ',' << "Infinity" << '\n';
						if (alpha != -10000 && beta != 10000)	a_b_log << name[l % 10] << l / 10 + 1 << ',' << depth - cut_off_depth << ',' << temp_string<< ',' << alpha << ',' << beta << '\n';
					}
				}
				
				
					
					
					
				
				
			
			
				
			
	   		}
			return temp;
	   //	}
	   	
	   	
		
		
	   }
}
}

void a_b(char **board, char cur_player, int cut_off_depth)
{	char name[8]={'a','b','c','d','e','f','g','h'};
	cout<<max_value(board,cur_player,cut_off_depth,cut_off_depth,-1,-10000,10000,0,0);
	if(a_b_best_step!=-1)flipboard(board,cur_player,a_b_best_step);
	
		ofstream fileStream("output.txt", ios_base::out);
	if (!fileStream)
	{
		cout << "fail" << endl;
	}
	else
	{
		for(int m=0;m<8;m++)
		{
			for(int n=0;n<8;n++)
			{
				fileStream << board[m][n]  ;
			}
			fileStream<<endl;
		}
		fileStream<<"Node,Depth,Value,Alpha,Beta"<<endl;
		fileStream<<a_b_log.str()<<endl;
	}
	fileStream.close();
}
int main()
{	char name[8]={'a','b','c','d','e','f','g','h'};
	fstream file;
	int LINES;
	file.open("input.txt", ios::in);
	if (file.fail())
	{
		cout << "file not exist" << endl;
		file.close();
	}
	else//ÎÄ¼þ´æÔÚ  
	{
		LINES = 11;
		string *temp = new string[LINES];//16
		int i = 0;
		int j = 0;
		for (i = 0; i < LINES; i++) //read string by line
		{
			getline(file, temp[i], '\n');
			if (temp[i][temp[i].length() - 1] == '\r')
				temp[i].erase(temp[i].length() - 1);

		}
		int method;
		char cur_player;
		int cut_off_depth;
		stringstream(temp[0]) >> method;
		cur_player = temp[1].at(0);
		stringstream(temp[2]) >> cut_off_depth;


		/* initial board*/
		char **board;
		board = new char *[8];
		for (i = 0; i < 8; i++)
		{
			board[i] = new char[8];
		}




		for (i = 0; i < 8; i++)
		{
			for (j = 0; j < 8; j++)
			{
				board[i][j] = temp[3 + i].at(j);
			
			}
		}

		player=cur_player;
		cout<<player;
		file.close(); //¹Ø±ÕÎÄ¼þ  	 

		switch (method)
		{
		case 1:greedy(board, cur_player); break;
		case 2:min_max(board, cur_player, cut_off_depth,1); break;
		case 3:a_b(board, cur_player, cut_off_depth); break;
		default:break;
		}

	//		flipboard(board,cur_player,24);
	//		flipboard(board,'X',25);
	//	vector<int> v=next_step(board,'O');
	//	for(i=0;i<v.size();i++) cout<<"position:"<<name[v.at(i)%10]<<v.at(i)/10+1<<endl;
		//	flipboard(board,cur_player,42);
//show_board(board);
//cout<<evaluate(board,'O');	


	}
}
