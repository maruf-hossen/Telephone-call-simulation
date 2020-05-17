#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
class waitPross{
	public: int from,to,length,arrtime;
};
class callInPross{
	public:
	int from,to,end;
};
class procced{
	public:
	int exicuted,succed,busy,blocked;	
};
void display(vector<waitPross> &waitTable,vector<callInPross> & proccesTable,waitPross next,int clock,int max,int used,vector<int>flag,procced proccess) {
	cout << "Waiting Table:" << endl << "From To Arrived length" << endl;
	for(int i = 0; i < waitTable.size(); i++)
		cout << waitTable[i].from << "	" <<waitTable[i].to << " " << waitTable[i].arrtime <<" " << waitTable[i].length << endl;
	cout << "Running Proccess:" << endl << "From To End" << endl;
	for(int i = 0; i < proccesTable.size(); i++)
		cout << proccesTable[i].from << " " << proccesTable[i].to << " " << proccesTable[i].end << endl;
	cout << "Next Call:" << endl << "From To Length" << endl;
	cout << next.from << " " << next.to << " " << next.length << endl;
	cout << "Arrival Time of Next call : " << endl << next.arrtime << endl;
	cout << "Clock " << clock << endl << "Max links " << max << endl << "Used links :" << used << endl;
        cout << "User Status:" <<endl;
	for(int i = 1;i < flag.size(); i++)
		cout << i << " " << flag[i] << endl;	
	cout << "Succed :" <<proccess.succed << endl << "Got Busy :" <<proccess.busy << endl << "Blocked :" <<proccess.blocked << endl;
        cout << "Total Exicuted :" <<proccess.exicuted << endl;
}
void simulate(vector<waitPross> &waitting, vector<callInPross>& running, waitPross &next, int &clock, int &max, int &used, vector<int>&flag,procced &proccess){
	callInPross temp;
	for(int i = 1; i < running.size(); i++){
		
		for(int j = i - 1; j >= 0; j--){
			if(running[i].end > running[j].end){
				temp = running[i];
				running[i] = running[j];
				running[j] = temp;
			}
		}
	}
	if(!running.empty()){	
		if(next.arrtime > running[running.size() - 1].end){
			temp = running.back();
			running.pop_back();
			flag[temp.from] = 0;
			flag[temp.to] = 0;
			used = used - 1;
			proccess.exicuted = proccess.exicuted + 1;
			proccess.succed = proccess.succed + 1;
			clock = temp.end;
		}	
		else if(next.arrtime == running[running.size() - 1].end){
			temp = running.back();
			running.pop_back();

			flag[temp.from] = 0;
			flag[temp.to] = 0;
			used = used - 1;
			proccess.exicuted = proccess.exicuted + 1;
			proccess.succed = proccess.succed + 1;
			clock = temp.end;
			if(!flag[next.from] && !flag[next.to]){
				temp.from = next.from;
				temp.to = next.to;
				temp.end = clock + next.length;
				running.push_back(temp);
				flag[next.from] = 1;
				flag[next.to] = 1;
				used = used + 1;
				if(!waitting.empty()){
				next = waitting.back();
				waitting.pop_back();
				}
				else{
					next.arrtime = 99999999;
					next.from = 0;
					next.to = 0;
				}
			}
		}
		else{
			clock = next.arrtime;
			if(!flag[next.from] && !flag[next.to]){
				if(running.size() < max){
					temp.from = next.from;
					temp.to = next.to;
					temp.end = clock + next.length;
					running.push_back(temp);
					flag[next.from] = 1;
					flag[next.to] = 1;
					used = used + 1;
					if(!waitting.empty()){
						next = waitting.back();
						waitting.pop_back();
					}
					else{
						next.arrtime = 99999999;							next.from = 0;
						next.to = 0;
					}
				}
				else{
					proccess.exicuted = proccess.exicuted + 1;
					proccess.blocked = proccess.blocked + 1;
					if(!waitting.empty()){
						next = waitting.back();
						waitting.pop_back();
					}
					else{
						next.arrtime = 99999999;
						next.from = 0;
						next.to = 0;
					}
				}
			}
			else{
				proccess.exicuted = proccess.exicuted + 1;
				proccess.busy = proccess.busy + 1;
				if(!waitting.empty()){
					next = waitting.back();
					waitting.pop_back();
				}
				else{
					next.arrtime = 99999999;
					next.from = 0;
					next.to = 0;
				}
			}
		}
	}
	else{
		if(!waitting.empty()){
			temp.from = next.from;
			temp.to = next.to;
			temp.end = next.arrtime +  next.length;
			running.push_back(temp);
			flag[next.from] = 1;
			flag[next.to] = 1;
			used = used + 1;
			clock = next.arrtime;
			next = waitting.back();
			waitting.pop_back();
		}
		else if(next.from != 0){
			temp.from = next.from;
			temp.to = next.to;
			temp.end = next.arrtime +  next.length;
			running.push_back(temp);
			clock = next.arrtime;
			flag[next.from] = 1;
			flag[next.to] = 1;
			used = used + 1;
			next.from = 0;
			next.arrtime = 99999999;
		}
	}
}

	
int main(){

	vector<waitPross>waitting;
	vector<callInPross>proccessing;
	waitPross nextCall;
	int clock;
	int maxLinks =  0;
	int usedLinks = 0;
	cout << "Enter Cloock and Maximum Link number with whitespace " << endl;
	cin >> clock >> maxLinks;
	vector<int>flag(maxLinks*2 + 1);
	for(int i = 0; i <= 2* maxLinks; i++)
		flag[i] = 0;
	cout << "Enter how many process do you want to proccess ? " <<endl;
	int procAmount;
	cin >> procAmount;
	cout << "Enter each of those From -----To --- Arrival_time---- length"<<endl;
	waitPross process;
	for(int i = 0; i < procAmount; i++){
		cin >> process.from >> process.to >> process.arrtime >> process.length;
		waitting.push_back(process);
	}
	cout << "Enter how many proccess in the Call in process table?" << endl;
	int numCallProc;
	cin >> numCallProc;
	usedLinks = numCallProc;
	callInPross callProc;
	cout << "From ---------- To -------------End" << endl;
	for(int i = 0; i < numCallProc; i++){
		cin >> callProc.from >> callProc.to >> callProc.end;
		flag[callProc.from] = 1;
		flag[callProc.to] = 1;
		proccessing.push_back(callProc);	
	}
	procced proccess;
	cout << "Enter the Current prograss of the simulator: " << "Total proccess Succed Busy Blocked " << endl;
	cin >>proccess.exicuted >> proccess.succed >> proccess.busy >> proccess.blocked; 
	waitPross temp;
	for(int i = 1; i < waitting.size(); i++){
		for(int j = i - 1; j >= 0; j--){
			if(waitting[i].arrtime > waitting[j].arrtime){
				temp = waitting[i];
				waitting[i] = waitting[j];
				waitting[j] = temp;
			}
		}
	}
	nextCall = waitting.back();
	waitting.pop_back();
	while(!proccessing.empty() || !waitting.empty() || nextCall.from){
	       display(waitting, proccessing, nextCall, clock, maxLinks, usedLinks, flag,proccess);
	       simulate(waitting,proccessing,nextCall,clock,maxLinks,usedLinks,flag,proccess);
	       int a;
	       cin >> a;
	}
	display(waitting, proccessing, nextCall, clock, maxLinks, usedLinks, flag,proccess);
	return 0;
}
