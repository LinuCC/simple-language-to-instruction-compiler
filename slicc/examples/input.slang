program my_prog {
    // Dies ist ein Kommentar
    int i = 0;
    int y;
    int foo = 5;
    int[5] bar;
    int barsize = 5;
    
    foo = i + 5;
    
    for (y < barsize; y = y + 1) {
      bar[y] = x + y;
    }
    call_by_value(foo);
    call_by_reference(y);
    foo = call_with_return(y);
    write(foo);
}

func void call_by_value(int val) {
  write(val);
}

func void call_by_reference(ref int val) {
  read(val);
}

func int call_with_return(int val) {
  int x = 2;
  return x / 2 + val * 2;
}
