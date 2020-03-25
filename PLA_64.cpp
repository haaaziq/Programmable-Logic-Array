//Generating PLA Program Table

#include<iostream>
#include<vector>
#include<bitset>
#include<set>
#include<algorithm>
#include<math.h>
using namespace std;

//Function for converting Minterms to Binary Equivalent
    string convert_to_binary (int minterm, int var){
        string bin;
            for(int i = 0; i < var; i++){
                if(minterm % 2 == 0)
                    bin.push_back('0');
                else
                    bin.push_back('1');
                minterm = minterm/2;
            }
            reverse(bin.begin(), bin.end());
            return bin;
    }

//Function for checking the number of 1's in binary string
    int checking1s( string a ){
        int count = 0;
        for(int i = 0; i < a.size(); i++){
            if(a[i] == '1')
                count++;
        }
        return count;
    }

//Function to check if two strings differ exactly at one position or they are same
    int compare(string a, string b){
        int count = 0, d = 0;
        for(int i = 0; i < a.length(); i++){
                if(a[i] != b[i])
                    count++;
                else if(a[i] = b[i])
                    d++;
        }
            if(count == 1)
                return 1;
            else if(d == a.length())
                return -1;
            else
                return 0;
    }

//Function to replace the differ position of two strings by '_'
    string diffposn(string a, string b){
        for(int i = 0; i < a.length(); i++){
			if (a[i] != b[i])
				a[i]='_';
		}
		return a;
    }

//Function to store unlike string in vector
    void check_like(string a,vector<string>&b){
        int flag = 0,len;
        len = b.size();
        for(int i = 0; i < len; i++){
            if(compare(a,b[i]) == -1)
                return;
            else
                flag++;
        }
            if(flag == len)
                b.push_back(a);
                return;
    }

//Function to converts binary string to alphabetic variables
    string bin_to_var(string x){
		string var = "";
		for (int i = 0; i < x.size(); ++i){
			if (x[i] == '1'){
				char x = 65 + i;
				var += x;
			}
			else if (x[i] == '0'){
				char x = 65 + i;
				var += x;
				var += "'";
			}
		}
		return var;
	}

/////////////////////////////////////////
/////////////////////////////////////////

    int main(){
        int m, n;
            cout << "Enter the no. of functions : ";
            cin >> n;

            cout << "Number of variables : ";
            cin >> m;
            cout << endl;

        vector<vector<int> > n1;
        vector<vector<string> >func;

        for(int i = 0; i < n; i++){
            vector<int> temp;
            int m1;
            cout << "Enter the no. of Minterms of Function " << i+1 << ": ";
            cin >> m1;

            cout << "Enter Minterms (F" << i + 1 << ") : ";
            for(int j = 0; j < m1; j++){
                int a;
                cin >> a;
                temp.push_back(a);
            }

            n1.push_back(temp);
            cout << endl;
        }

        for(int i = 0; i < n; i++){
            int k = 0;
            vector<int> temp0;
                for(int j = 0; j < pow(2,m); j++){
                    if( n1[i][k] != j )
                        temp0.push_back(j);
                    else
                        k++;
                }
            n1.push_back(temp0);
        }

    //For printing stored minterms
        for(int i = 0; i < n; i++){
            cout << "F(" << i + 1 << ") = ";
            for(int j = 0; j < n1[i].size(); j++){
                cout << n1[i][j] <<" ";
            }
                cout << endl;
        }
            cout << endl;

    //Minimization using Quine McCluskey Technique
    //Running loop first for functions and then for its complements
        for(int i = 0; i < 2*n; i++){
                if (i < n )
                    cout  <<  "F(" << i + 1 << ") : " << endl;
                if (i >= n ){
                    cout  <<  "F(" << i + 1 - n << ")' : " << endl;
                    }
                int n2 = n1[i].size();
                int a[n2];
                vector<string> vect;
                vector<string> terms;
                vector<string> temp1;
                vector<string> pi;
                vector<string> epi;
                vector<int> temp2;

                    for(int j = 0; j < n2; j++)
                        a[j] = n1[i][j];
                    for(int i = 0; i < n2; i++)
                        vect.push_back(convert_to_binary(a[i],m));
                    for(int i = 0; i < vect.size(); i++)
                        terms.push_back(vect[i]);

            int i,j,k;
            while(!vect.empty()){

                for(i = 0; i < vect.size()-1; i++){
                    int c=0;
                    for(j = i+1; j < vect.size(); j++){
                        int l = compare(vect[i],vect[j]);
                        if( l == 1 ){
                            temp1.push_back(diffposn(vect[i],vect[j]));
                            temp2.push_back(j);
                        }
                        else
                            c++;
                    }

                        if(c == j-i-1){
                            int d = 0;
                            for(int k = 0; k < temp2.size(); k++){
                                if(i == (temp2[k])){
                                    d=1;
                                    break;
                                }
                            }
                            if(d == 0)
                                check_like(vect[i],pi);
                        }
                }
            int d = 0;

                for(int k = 0;k < temp2.size(); k++){
                    if(i == (temp2[k])){
                        d=1;
                        break;
                    }
                }
                if(d==0)
                    check_like(vect[i],pi);
                        vect.clear();
                for(int i = 0; i< temp1.size(); i++){
                    vect.push_back(temp1[i]);
                }
                temp1.clear();
                temp2.clear();
            }

            vector<string>().swap(temp1);
            vector<int>().swap(temp2);
            vector<string>().swap(vect);
                cout << "Prime Implicants: " << endl;
                for(int i = 0; i < pi.size(); i++){
                        cout << bin_to_var(pi[i]) << " ";
                }

                int row, column, count;
                vector<pair<int,int> >temp3;
                vector<string> esspi;

            	row = pi.size();
                column = n2;
                int**t = new int*[row+1];
                    for(int i = 0; i < row+1; i++){
                        t[i] = new int[column];
                    }

                    for(int i = 0; i < row+1; i++){
                        for(int j = 0; j < column; j++)
                            t[i][j] = 0;
                    }
                    for(int i = 0; i < row; i++){
                        int c;
                        int n3 = terms.size();
                        int l1 = pi[i].length();
                        for(int j = 0; j < n3; j++){
                            c=1;
                            for(int k = 0; k < l1; k++){
                                if(pi[i][k] != '_'){
                                        if(pi[i][k] != terms[j][k]){
                                            c=0;
                                            break;
                                        }
                                }
                            }
                            if(c==1)
                                t[i][j]=1;
                        }
                     }
                    for(j = 0; j < column; j++){
                        count = 0;
                        for(i = 0; i < row; i++){
                            if(t[i][j] == 1){
                                count++;
                                k = i;
                            }
                        }
                        if(count == 1){
                        temp3.push_back(make_pair(j,k));
                        }
                    }

                    for(i = 0; i < temp3.size(); i++){
                        if(t[row][temp3[i].first] != 1){
                            epi.push_back(pi[temp3[i].second]);
                            t[temp3[i].second][temp3[i].first] = -1;
                            t[row][temp3[i].first] = 1;
                            for(j = 0; j < column; j++){
                                if(t[temp3[i].second][j] == 1){
                                    for(k = 0; k < row; k++){
                                        if(t[k][j] == 1)
                                            t[k][j] = -1;
                                    }
                                    t[row][j] = 1;
                                }
                            }
                        }
                    }
                    temp3.clear();

                    for(i = 0; i < row; i++){
                        count=0;
                        for(j = 0; j < column; j++){
                            if(t[i][j] == 1)
                                count++;
                        }
                        if(count > 0){
                            temp3.push_back(make_pair(count,i));
                        }
                    }
                    sort(temp3.begin(),temp3.end());

                    if(!temp3.empty()){
                            i = temp3.size()-1;
                            epi.push_back(pi[temp3[i].second]);
                            for(j = 0; j < column; j++){
                                if(t[temp3[i].second][j] == 1){
                                    for(k = 0; k < row; k++){
                                        if(t[k][j] == 1){
                                            t[k][j] = -1;
                                        }
                                    }
                                }
                            }

                    //While Loop for checking for Essential Prime Implicants(epi)
                        while(1){
                            k=1;
                            for(i = 0; (i < temp3.size()-k && i >= 0); i++){
                                count=0;
                                for(j = 0; j < column; j++){
                                    if(t[temp3[i].second][j] == 1)
                                        count++;
                                }
                                if(count>0){
                                    temp3[i].first = count;
                                }
                                else
                                    temp3[i].first = 0;
                            }

                            sort(temp3.begin(),temp3.end()-k);
                            i = temp3.size()-1-k;
                            if(temp3[i].first > 0){
                                epi.push_back(pi[temp3[i].second]);
                                for(j = 0; j < column; j++){
                                    if(t[temp3[i].second][j] == 1){
                                        for(k = 0; k < row; k++){
                                            if(t[k][j] == 1){
                                                t[k][j] = -1;
                                            }
                                        }
                                    }
                                }
                            }
                            else
                                break;
                                k++;
                        }
                            cout << endl;
                            cout << "Essential Prime Implicants: " << endl;
                            for(int i = 0; i < epi.size(); i++){
                                cout << bin_to_var(epi[i]) << "  ";
                                esspi.push_back(epi[i]);
                            }
                    }
                    else{
                        cout << endl;
                        cout << "Essential Prime Implicants: " << endl;
                        for(int i = 0; i < pi.size(); i++){
                            cout << bin_to_var(pi[i]) << "  ";
                            esspi.push_back(pi[i]);
                        }
                    }

                    func.push_back(esspi);
                    cout << endl << endl;
        }

            //Printing Minimized Functions(both F and F')
                cout << "Minimized Functions are : " << endl;
                for(int i = 0; i < func.size(); i++){
                    int x = func.size();
                    if (i < x/2 )
                        cout  <<  "F(" << i + 1 << ") = ";
                    if (i >= x/2 ){
                        cout  <<  "F(" << i + 1 - x/2 << ")' = ";
                    }
                    for(int j = 0; j < func[i].size(); j++){
                         cout  << bin_to_var(func[i][j]) << " ";
                    }
                    cout << endl;
                }
                cout << endl << endl;

                vector<string> w;

                for(int i = 0; i < pow(2,n); i++)
                    w.push_back(convert_to_binary(i,n));

            //Grouping the possible arrangements
                vector<set<string> > fnc;
                for(int i = 0; i < w.size(); i++){
                     set<string> temp4;
                     for(int j = 0; j < w[i].size(); j++){
                         if(w[i][j] == '0'){
                             for(int k = 0; k < func[j+n].size(); k++)
                                 temp4.insert(func[j+n][k]);
                         }
                         else{
                             for(int k = 0; k < func[j].size(); k++)
                             temp4.insert(func[j][k]);
                         }
                     }
                     fnc.push_back(temp4);
                 }

			//check that which set of function have minimum no. of terms
                 int min = fnc[0].size();
                 int res = 0;
                 for(int i = 1; i < pow(2,n); i++){
                     if(min > fnc[i].size()){
                         res = i;
                         min = fnc.size();
                     }
                 }

                //Print functions with most common product terms
                    string s = (convert_to_binary(res,n));
                    cout << "Functions in which less no. of AND Gates required or with most common product terms are: " << endl;
                    for(int i = 0; i < s.size(); i++){
                        if(s[i] == '0')
                            cout << "F(" << i+1 << ")' " << endl;
                        else
                            cout << "F("<< i+1 << ") " << endl;
                    }
                    cout << endl;
                    cout << "Terms of these functions can be seen above.";
                    cout << endl << endl;

                //Print the table

                  /*  cout << "PLA Program Table:" << endl;
                    cout << "Product Terms\t\t";
                        for(int i = 0; i < m; i++){
                            char x = 65 + i;
                            cout << x << "\t";
                        }
                            cout << "\t\t";
                        for(int i = 0; i < n; i++){
                            cout << "F(" << i + 1 << ")\t";
                        }
                        cout << endl;

                        for(int i = 0; i <= min; i++){
                                cout << i + 1 << " - ";
                            for(int j = 0; j <= n+m+2; j++){

                                             //cout  << bin_to_var(func[i][j]) << " ";
                                        }
                            cout << endl;

                        }*/

                cout << endl << endl;

    return 0;
}
/*

Mohammad Haziq Khan
B.Tech II Year
Faculty No. : 18COB542
Enrollment No. : GJ2844
Class Sr. No. : 64

*/
