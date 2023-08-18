int read() {
    int r = 0, f = 1;
    char c = getchar();

    while (c < '0' || c > '9') {
        if (c == '-')
            f = -1;

        c = getchar();
    }

    while (c >= '0' && c <= '9') {
        r = (r << 1) + (r << 3) + c - 48;
        c = getchar();
    }

    return r * f;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand(time(0));
}