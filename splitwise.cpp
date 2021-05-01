#include<bits/stdc++.h>
using namespace std;

class person_comparator {
public:
	bool operator()(pair<string, int> p1, pair<string, int> p2) {
		return p1.second < p2.second;
	}
};
int main() {
	int no_of_transactions, no_of_friends;
	cin >> no_of_transactions >> no_of_friends;
	string x, y;
	int amount;

	//Making a map to store the net amount that each person will have to take at the end
	map<string, int> net;
	while (no_of_transactions--) {
		cin >> x >> y >> amount; //x gives 'amount' to y
		if (net.count(x) == 0) net[x] = 0;
		if (net.count(y) == 0) net[y] = 0;
		net[x] -= amount;
		net[y] += amount;
	}
	//we now know net amount for every person
	//now, iterate over all the nodes, if net[current_node]!=0 put it in multiset
	//Multiset => Initialize a list and sort it.
	multiset<pair<string, int>, person_comparator> m; //multiset because two nodes can have same net value
	for (auto p : net) {
		string person = p.first;
		int amt = p.second;
		if (net[person] != 0) {
			m.insert(make_pair(person, amt));
		}
	}

	int cnt = 0;
	//Pop out two persons from right and left and try to settle them
	while (!m.empty()) {
		auto left = m.begin();
		auto right = prev(m.end()); //can't do m.end()-1

		int debit = left->second;
		string debit_person = left->first;

		int credit = right->second;
		string credit_person = right->first;


		//erase
		m.erase(left);
		m.erase(right);
		//settlement
		int settlement_amount = min(-debit, credit);
		//one of debit,credit will become 0 because settlement amount is equal to debit or credit
		debit += settlement_amount; //-5+2
		credit -= settlement_amount; //5-2

		//Printing the transaction between people
		cout << debit_person << " pays " << settlement_amount << " to-> " << credit_person << endl;
		if (debit != 0) {
			m.insert(make_pair(debit_person, debit));
		}
		if (credit != 0) {
			m.insert(make_pair(credit_person, credit));
		}
		cnt++;

	}
	cout << cnt << endl;

	return 0;
}
