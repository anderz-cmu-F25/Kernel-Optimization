// pack a row major order matrix (mc x k) into 
// (mc / m) panels that are each (m x k), and column major order
void pack(double* pack_a, double* a, int mc, int m, int k) {
    const int panels = mc / m;
    const int panel_size = m * k;

    for (int i = 0; i < panels; i++) {
        for (int p = 0; p < k; p++) {
            for (int j = 0; j < m; j++) {
                pack_a[i * panel_size + p * m + j] = a[(i * m + j) * k + p];
            }
        }
    }
}
