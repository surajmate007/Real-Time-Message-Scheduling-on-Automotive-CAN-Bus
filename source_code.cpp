#include<bits/stdc++.h>
#include<fstream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

float macsize, tgen, tver;

// Function to compute Cm
float getCm(int size, int bw){
    float ans = 0.0;
    ans = (floor((34 + 8 * size)/5) + 47 + 8 * size)/(bw);
    return ans;
}

// 0th -> priority, 1st -> id, 2nd -> size, 3rd -> jitter, 4th -> Time Period, 5th -> Deadline, 6th -> 125kbps, 7th -> 250kbps, 8th -> 500kbps, 9th -> 1000kbps.

void canWeSchedule(vector<vector<float> >& info, int n, int m, float bw){
    priority_queue<pair<float, float> > pq;
	vector<float> nextSchedule(n);
	
    // First scheduling all the messages at time = 0.
	for(int i=0; i<n; i++){
		pq.push(make_pair(info[i][0], i));
        nextSchedule[i] = info[i][4];
	}
    	
	float timer = (130/bw)+tgen+tver;   // Only add mac generation and verification time for last less priority sender before start of transmission from high high priority sender.
    int maxtime = 1000;
    
    while(timer<=maxtime){
		if(!pq.empty()){
			int msg = pq.top().first; int idx = pq.top().second; pq.pop();
			float size =  info[idx][2]; // executing highest priority message
            // no need to add MAC generation and verification time because when other message is scheduled then the sender can side by side compute it and verifier can verify it.
			timer += getCm(size + macsize, bw);
			
			if(timer <= info[idx][5]){
                if(bw == 125 and info[idx][6] == -1){
                    info[idx][6] = timer;
                }
                else if(bw == 250 and info[idx][7] == -1){
                    info[idx][7] = timer;
                }
                else if(bw == 500 and info[idx][8] == -1){
                    info[idx][8] = timer;
                }
                else if(bw == 1000 and info[idx][9] == -1){
                    info[idx][9] = timer;
                }
            }
		}
		else{
			timer++;
		}
		// Checking which messages can be scheduled next
        for(int i=0; i<n; i++){
			if(timer >= nextSchedule[i]){
				pq.push(make_pair(info[i][0], i));
                nextSchedule[i] += info[i][4];
			}	
		}
    }
}

void fillForAll(vector<float>& bws, vector<vector<float> >& info, int n, int m){
    for(int i=0; i<bws.size(); i++){
        float bw = bws[i];
        canWeSchedule(info, n, m, bw);
    }
}

// Function to Generate Normal Table
void callToNormal(vector<float>& bws){
    int n = 53; int m = 10;
	vector<vector<float> > info(n, vector<float>(m, -1));
    ifstream file1("Normal.txt");
    float number;
    int i=0; int j=0;
    while(file1 >> number){
        info[i][j] = number;
        j++;
        if(j == 6){
            i++; j = 0;
        }
    }

	fillForAll(bws, info, n, m);

    cout<<endl<<endl<<"-----------------------------------------------  The Schedling Result for Normal Signals are as Follows  ----------------------------------------------- "<<endl<<endl<<setw(15);
    cout<<"Priority"<<setw(15)<<"Message ID"<<setw(15)<<"Size"<<setw(15)<<"Jitter"<<setw(15)<<"Time Period"<<setw(15)<<"Deadline"<<setw(15)<<"125 Kbps"<<setw(15)<<"250 Kbps"<<setw(15)<<"500 Kbps"<<setw(15)<<"1 Mbps"<<setw(15)<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout<<info[i][j]<<setw(15);
		}
		cout<<endl<<setw(15);
	}
}

// Function to Generate Piggybacked Table
void callToPiggybacked(vector<float>& bws){
    int n = 17; int m = 10;
    vector<vector<float> > pgb(n, vector<float> (m, -1));
    ifstream file2("piggybacked.txt");
    float number;
    int i=0; int j=0;
    while(file2 >> number){
        pgb[i][j] = number;
        j++;
        if(j == 6){
            i++; j = 0;
        }
    }

	fillForAll(bws, pgb, n, m);

    cout<<endl<<endl<<"-----------------------------------------------  The Schedling Result for Piggybacked Signals are as Follows  ----------------------------------------------- "<<endl<<endl<<setw(15);
    cout<<"Priority"<<setw(15)<<"Message ID"<<setw(15)<<"Size"<<setw(15)<<"Jitter"<<setw(15)<<"Time Period"<<setw(15)<<"Deadline"<<setw(15)<<"125 Kbps"<<setw(15)<<"250 Kbps"<<setw(15)<<"500 Kbps"<<setw(15)<<"1 Mbps"<<setw(15)<<endl;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			cout<<pgb[i][j]<<setw(15);
		}
		cout<<endl<<setw(15);
	}
}

int main(){
    vector<float> bws;
    bws.push_back(125);
    bws.push_back(250);
    bws.push_back(500);
    bws.push_back(1000);

    cout<<"Enter MAC size : ";
    cin>>macsize;
    cout<<"Enter MAC Generation Time : ";
    cin>>tgen;
    cout<<"Enter MAC Veriication Time : ";
    cin>>tver;

    callToNormal(bws);
    cout<<endl<<endl;
    callToPiggybacked(bws);
    
    return 0;
}