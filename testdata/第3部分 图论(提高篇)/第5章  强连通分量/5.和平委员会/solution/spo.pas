program SPO;
const
    maxn=16000;
type
    TLink=^TNode;
    TNode=record
        v:longint;
        next:TLink;
    end;
var
    g:array[1..maxn] of TLink;
    res:array[1..maxn div 2] of longint;
    sav:array[1..maxn] of longint;
    n,m,top:longint;

function opp(x:longint):longint;
begin
    if odd(x) then exit(x+1) else exit(x-1);
end;

procedure insert(x,y:longint);
var
    s:TLink;
begin
    new(s); s^.v:=y; s^.next:=g[x]^.next; g[x]^.next:=s;
end;

procedure init;
var
    i,j,k:longint;
begin
    assign(input,'SPO.in');reset(input);
    assign(output,'SPO.out');rewrite(output);
    readln(n,m);
    for i:=1 to 2*n do begin
        new(g[i]);
        g[i]^.next:=nil;
    end;
    for i:=1 to m do begin
        readln(j,k);
        insert(j,opp(k));
        insert(k,opp(j));
    end;
    close(input);
end;

function ok(x:longint):boolean;
var
    i,k:longint;
    s:TLink;
begin
    inc(top);
    sav[top]:=x;
    res[(x+1) div 2]:=x;

    s:=g[x]^.next;
    while s<>nil do begin
        i:=s^.v;
        k:=(i+1) div 2;
        if (res[k]=0) and not ok(i) or (res[k]<>i) then begin
            for i:=1 to top do res[(sav[i]+1) div 2]:=0;
            top:=0;
            exit(false);
        end;
        s:=s^.next;
    end;
    exit(true);
end;

procedure solve;
var
    i:longint;
begin
    for i:=n downto 1 do
        if res[i]=0 then begin
            top:=0;
            if ok(2*i-1) then res[i]:=2*i-1
                else if ok(2*i) then res[i]:=2*i
                    else begin
                        writeln('NIE');
                        close(output);
                        halt;
                    end;
        end;
    for i:=1 to n do writeln(res[i]);
end;

begin
    init;
    solve;
    close(output);
end.
