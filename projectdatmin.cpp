#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>

using namespace std;
struct DataPoint {
    int kabupaten;
    double x;
    int y;
    int z;
};

void printClusters(const vector<DataPoint>& data, const vector<vector<DataPoint>>& clusters) {
    cout << "Hasil Clustering:" << endl;
    
    // Menampilkan Cluster 1
    cout << "CLUSTER 1" << endl;
    for (const auto& point : clusters[4]) {
        cout << "Kabupaten/kota ke-" << point.kabupaten << endl;
    }
    cout << endl;
    
    // Menampilkan Cluster 2
    cout << "CLUSTER 2" << endl;
    for (const auto& point : clusters[2]) {
        cout << "Kabupaten/kota ke-" << point.kabupaten << endl;
    }
    cout << endl;
    
    // Menampilkan Cluster 3
    cout << "CLUSTER 3" << endl;
    for (const auto& point : clusters[3]) {
        cout << "Kabupaten/kota ke-" << point.kabupaten << endl;
    }
    cout << endl;
    
    // Menampilkan Cluster 4
    cout << "CLUSTER 4" << endl;
    for (const auto& point : clusters[0]) {
        cout << "Kabupaten/kota ke-" << point.kabupaten << endl;
    }
    cout << endl;
    
    // Menampilkan Cluster 5
    cout << "CLUSTER 5" << endl;
    for (const auto& point : clusters[1]) {
        cout << "Kabupaten/kota ke-" << point.kabupaten << endl;
    }
    cout << endl;
}

double calculateDistance(const DataPoint& point1, const DataPoint& point2) {
    double distX = point1.x - point2.x;
    int distY = point1.y - point2.y;
    int distZ = point1.z - point2.z;
    return sqrt(distX * distX + distY * distY + distZ * distZ);
}

vector<DataPoint> calculateCentroids(const vector<vector<DataPoint>>& clusters) {
    vector<DataPoint> centroids;
    for (const auto& cluster : clusters) {
        double sumX = 0.0;
        int sumY = 0;
        int sumZ = 0;
        for (const auto& point : cluster) {
            sumX += point.x;
            sumY += point.y;
            sumZ += point.z;
        }
        double centroidX = sumX / cluster.size();
        int centroidY = sumY / cluster.size();
        int centroidZ = sumZ / cluster.size();
        centroids.push_back({0, centroidX, centroidY, centroidZ});
    }
    return centroids;
}

int findNearestCluster(const DataPoint& point, const vector<DataPoint>& centroids) {
    int nearestCluster = 0;
    double minDistance = numeric_limits<double>::max();
    for (int i = 0; i < centroids.size(); i++) {
        double distance = calculateDistance(point, centroids[i]);
        if (distance < minDistance) {
            minDistance = distance;
            nearestCluster = i;
        }
    }
    return nearestCluster;
}

void kMeansClustering(vector<DataPoint>& data, int k) {
    vector<DataPoint> centroids(k);
    vector<vector<DataPoint>> clusters(k);

    // Inisialisasi posisi awal centroid secara acak
    random_shuffle(data.begin(), data.end());
    for (int i = 0; i < k; i++) {
        centroids[i] = data[i];
    }

    bool converged = false;
    int iteration = 0;

    while (!converged) {
        // Mengosongkan kluster
        for (int i = 0; i < k; i++) {
            clusters[i].clear();
        }

        // Menentukan kluster tiap data
        for (const auto& point : data) {
            int nearestCluster = findNearestCluster(point, centroids);
            clusters[nearestCluster].push_back(point);
        }

        // Menghitung posisi centroid baru
        vector<DataPoint> newCentroids = calculateCentroids(clusters);

        // Cek konvergensi
        converged = true;
        for (int i = 0; i < k; i++) {
            if (calculateDistance(centroids[i], newCentroids[i]) > 1e-10) {
                converged = false;
                break;
            }
        }

        // Memperbarui posisi centroid
        centroids = newCentroids;

        // Menampilkan hasil setiap iterasi
        cout << "Iterasi " << iteration + 1 << endl;
        printClusters(data, clusters);

        iteration++;
    }
}

int main() {
    vector<DataPoint> data = {
        {1, 9, 10301, 10},
        {2, 5, 7596, 38},
        {3, 10, 10095, 13},
        {4, 10, 9003, 25},
        {5, 9, 7621, 27},
        {6, 10, 9861, 25},
        {7, 4, 6479, 37},
        {8, 4, 5379, 36},
        {9, 10, 11631, 14},
        {10, 9, 8074, 20},
        {11, 6, 6321, 26},
        {12, 5, 5838, 26},
        {13, 4, 4818, 38},
        {14, 3, 5511, 30},
        {15, 4, 4916, 33},
        {16, 9, 6723, 14},
        {17, 8, 8943, 17},
        {18, 9, 6865, 30},
        {19, 9, 5726, 38},
        {20, 6, 4668, 29},
        {21, 1, 4047, 38},
        {22, 3, 4437, 39},
        {23, 3, 4548, 37},
        {24, 3, 4734, 34},
        {25, 2, 5482, 37},
        {26, 5, 5479, 30},
        {27, 3, 5387, 42},
        {28, 3, 4724, 43},
        {29, 11, 14916, 11}
    };

    int k = 5; // Jumlah cluster

    kMeansClustering(data, k);

    return 0;
}

