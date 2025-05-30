#include<iostream>
#include<algorithm>
#include<fstream>
#include<sstream>
#include<stack>
#include<queue>
#include<vector>
#include <functional>
using namespace std;

//Chuyển ma trận kề sang danh sách kề
// Ý tưởng: Duyệt toàn bộ ma trận, nếu tại vị trí [i][j] = 1 nghĩa là có cạnh i → j,
//         ta thêm j vào danh sách kề của đỉnh i.
vector<vector<int>> convertMatrixToList(const string& filename) {
	ifstream fin(filename);
	int n;
	fin >> n;
	vector<vector<int>> list(n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0, val; j < n; ++j) {
			fin >> val;
			if (val) list[i].push_back(j);
		}
	}
	return list;
}

//Chuyển danh sách kề sang ma trận kề
// Ý tưởng: Khởi tạo ma trận nxn toàn 0. Sau đó với mỗi dòng,
//         đọc số lượng đỉnh kề rồi gán 1 vào vị trí adjMatrix[i][v] với v là đỉnh kề.
vector<vector<int>> convertListToMatrix(const string& filename) {
	ifstream fin(filename);
	int n;
	fin >> n;
	vector<vector<int>> matrix(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		int counter, add;
		fin >> counter;
		for (int j = 0; j < counter; j++) {
			fin >> add;
			matrix[i][add] = 1;
		}
	}
	return matrix;
}

//Hàm kiểm tra ma trận có hướng
// Ý tưởng: Nếu tồn tại i ≠ j mà adjMatrix[i][j] ≠ adjMatrix[j][i] thì đồ thị có hướng
//         (vì đồ thị vô hướng thì ma trận kề phải đối xứng).
bool isDirected(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] != adjMatrix[j][i]) {
				return true;
			}
		}
	}
	return false;
}


//Hàm đếm số đỉnh
// Ý tưởng: Kích thước ma trận là số đỉnh n.
int countVertices(const vector<vector<int>>& adjMatrix) {
	return adjMatrix.size();
}

//Hàm đếm số cạnh
// Ý tưởng: Cộng tất cả phần tử có giá trị 1 trong ma trận:
//          - Nếu là đồ thị có hướng thì tổng là số cạnh.
//          - Nếu là đồ thị vô hướng thì phải chia đôi (vì mỗi cạnh xuất hiện 2 lần).
int countEdges(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	int adges = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j]) {
				adges++;
			}
		}
	}
	if (isDirected(adjMatrix)) {
		return adges;
	}
	else {
		return adges / 2;
	}
}

//Hàm kiểm tra đỉnh cô lập
// Ý tưởng: Một đỉnh cô lập nếu hàng và cột của nó trong ma trận toàn số 0.
vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> isolated;
	for (int i = 0; i < n; ++i) {
		bool isolatedFlag = true;
		for (int j = 0; j < n; ++j)
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				isolatedFlag = false;
				break;
			}
		if (isolatedFlag) isolated.push_back(i);
	}
	return isolated;
}

//Kiểm tra đồ thị vô hướng có đầy đủ không
// Ý tưởng: Đồ thị đầy đủ có cạnh giữa mọi cặp đỉnh phân biệt =>
//          adjMatrix[i][j] = 1 với mọi i ≠ j.
bool isCompleteGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	for (int i = 0; i < n; ++i)
		for (int j = 0; j < n; ++j)
			if (i != j && adjMatrix[i][j] == 0)
				return false;
	return true;
}

//Hàm kiểm tra đồ thị lưỡng phân hay không
// Ý tưởng: Dùng BFS để tô màu 2 màu xen kẽ. Nếu phát hiện 2 đỉnh kề cùng màu → sai.
//Tham khảo chatGPT
bool isBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1); // -1: chưa tô màu
	for (int start = 0; start < n; ++start) {
		if (color[start] != -1) continue;
		queue<int> q;
		q.push(start);
		color[start] = 0;
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v]) {
					if (color[v] == -1) {
						color[v] = 1 - color[u];
						q.push(v);
					}
					else if (color[v] == color[u]) {
						return false;
					}
				}
			}
		}
	}
	return true;
}

//Hàm kiểm tra đồ thị lưỡng phân đầy đủ hay không
// Ý tưởng: Dựa trên isBipartite. Nếu đúng, thì kiểm tra các đỉnh thuộc 2 tập,
//          mọi cặp giữa 2 tập phải có cạnh, mọi cặp trong cùng tập thì không.
bool isCompleteBipartite(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<int> color(n, -1);
	vector<int> part[2];
	for (int start = 0; start < n; ++start) {
		if (color[start] != -1) continue;
		queue<int> q;
		q.push(start);
		color[start] = 0;
		part[0].push_back(start);
		while (!q.empty()) {
			int u = q.front(); q.pop();
			for (int v = 0; v < n; ++v) {
				if (adjMatrix[u][v]) {
					if (color[v] == -1) {
						color[v] = 1 - color[u];
						part[color[v]].push_back(v);
						q.push(v);
					}
					else if (color[v] == color[u])
						return false;
				}
			}
		}
	}
	for (int u : part[0])
		for (int v : part[0])
			if (u != v && adjMatrix[u][v]) return false;
	for (int u : part[1])
		for (int v : part[1])
			if (u != v && adjMatrix[u][v]) return false;
	for (int u : part[0])
		for (int v : part[1])
			if (!adjMatrix[u][v]) return false;
	return true;
}

//Hàm tạo đồ thị vô hướng tương ứng
//Ý tưởng: Nếu có cạnh i → j hoặc j → i thì thêm cả hai cạnh.
vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> answerGraph(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (adjMatrix[i][j] || adjMatrix[j][i]) {
				answerGraph[i][j] = 1;
				answerGraph[j][i] = 1;
			}
		}
	}
	return answerGraph;
}

//Hàm tạo đồ thị bù
// Ý tưởng: Nếu i ≠ j và không có cạnh i-j thì thêm cạnh vào đồ thị bù.
vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> answerGraph(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j && adjMatrix[i][j] == 0) {
				answerGraph[i][j] = 1;
			}
		}
	}
	return answerGraph;
}

//Hàm tìm chu trình Euler
// Ý tưởng: Dùng stack để lần theo cạnh chưa đi, khi quay lui thì thêm vào chu trình.
vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<vector<int>> graph = adjMatrix;
	stack<int> st;
	vector<int> circuit;
	st.push(0);
	while (!st.empty()) {
		int u = st.top();
		int v;
		for (v = 0; v < n; ++v) {
			if (graph[u][v]) break;
		}
		if (v == n) {
			circuit.push_back(u);
			st.pop();
		}
		else {
			st.push(v);
			graph[u][v]--;
			graph[v][u]--;
		}
	}
	return circuit;
}

//Hàm tạo cây từ đồ thị vô hướng bằng DFS
//Tham khảo dùng thu viện functional
//Ý tưởng: Duyệt DFS bằng đệ quy, khi tìm thấy đỉnh mới, thêm cạnh vào cây.
vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	function<void(int)> dfs = [&](int u) {
		visited[u] = true;
		for (int v = 0; v < n; ++v)
			if (adjMatrix[u][v] && !visited[v]) {
				tree[u][v] = tree[v][u] = 1;
				dfs(v);
			}
		};
	dfs(start);
	return tree;
}

//Hàm tạo cây từ đồ thị vô hướng bằng BFS
// Ý tưởng: Duyệt đồ thị theo chiều rộng(BFS), gặp được đỉnh mới thì thêm vào cây.
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start) {
	int n = adjMatrix.size();
	vector<vector<int>> tree(n, vector<int>(n, 0));
	vector<bool> visited(n, false);
	queue<int> q;
	visited[start] = true;
	q.push(start);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v = 0; v < n; ++v)
			if (adjMatrix[u][v] && !visited[v]) {
				visited[v] = true;
				tree[u][v] = tree[v][u] = 1;
				q.push(v);
			}
	}
	return tree;
}

//Hàm kiểm tra 2 đỉnh u, v có nối nhau không
// Ý tưởng: Duyệt đồ thị theo chiều sâu bằng DFS bắt đầu từ 1 đỉnh nếu đến được đỉnh còn lại thì 2 đỉnh nối nhau.
bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix) {
	int n = adjMatrix.size();
	vector<bool> visited(n, false);
	stack<int> st;
	st.push(u);
	while (!st.empty()) {
		int curr = st.top(); st.pop();
		if (curr == v) return true;
		if (visited[curr]) continue;
		visited[curr] = true;
		for (int i = 0; i < n; ++i)
			if (adjMatrix[curr][i] && !visited[i])
				st.push(i);
	}
	return false;
}