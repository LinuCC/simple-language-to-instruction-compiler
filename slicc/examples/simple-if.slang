program simple_if {
    int i = 1;
    int k = 10;

    if (i >= 2) {
      k = 1;
    }

    if (i >= 1) {
      k = 2;
    }

    if (i >= 0) {
      k = 3;
    }

    if (i > 1) {
      k = 4;
    }

    if (i == 0) {
      i = 1;
    }

    if (i < 1) {
      i = 2;
      i = i + 1;
    } else {
      i = 2 * k + i;
    }
}
