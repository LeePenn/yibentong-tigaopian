{$A+,B-,D-,E-,F-,G+,I-,L-,N-,O-,P-,Q-,R-,S-,T-,V-,X-}
{$M 65520,0,655360}
program spo(input, output);

const fin = 'spo.in';
      fon = 'spo.out';

type link = ^node;
     node = record
              l :integer;
              next :link
            end;

var rel :array [1..16000] of link;
    n :integer;

procedure initialize;
 var x, y, m, i :integer;
     p :link;
 begin
   readln(n, m); n := n shl 1;
   for i := 1 to n do rel[i] := nil;
   for i := 1 to m do
     begin
       readln(x, y);
       new(p); p^.l := y; p^.next := rel[x]; rel[x] := p;
       new(p); p^.l := x; p^.next := rel[y]; rel[y] := p
     end
 end;

procedure solve;
 var app :array [1..16000] of shortint;
     op :array [0..16000] of integer;
     p :link;
     i, j, k, l :integer;
     b :boolean;
 label 1;
 begin
   fillchar(app, sizeof(app), 0);
   for i := 1 to n do
     begin
       if app[i] = 0
         then begin
                b := false;
                op[0] := 2; op[1] := i;
                app[i] := 1;
                if odd(i)
                  then begin
                         app[i + 1] := -1;
                         op[2] := i + 1
                       end
                  else begin
                         app[i - 1] := -1;
                         op[2] := i - 1
                       end;
                j := 1;
                while j <= op[0] do
                  begin
                    k := op[j];
                    if app[k] = -1
                      then begin
                             if odd(k) then l := k + 1 else l := k - 1;
                             if app[l] = 0
                               then begin
                                      app[l] := 1;
                                      inc(op[0]); op[op[0]] := l
                                    end;
                             if app[l] = -1
                               then begin
                                      b := true;
                                      goto 1
                                    end
                           end
                      else begin
                             p := rel[k];
                             while p <> nil do
                               begin
                                 l := p^.l;
                                 if app[l] = 0
                                   then begin
                                          app[l] := -1;
                                          inc(op[0]); op[op[0]] := l
                                        end;
                                 if app[l] = 1
                                   then begin
                                          b := true;
                                          goto 1
                                        end;
                                 p := p^.next
                               end
                           end;
                    inc(j)
                  end;
1:              if b then for j := 1 to op[0] do app[op[j]] := 0
              end;
       if (i and 1 = 0) and (app[i - 1] = 0) and (app[i] = 0) then break
     end;
   i := 1; b := false;
   while i < n do
     begin
       if app[i] * app[i + 1] <> -1
         then begin
                b := true;
                break
              end;
       inc(i, 2)
     end;
   if b then writeln('NIE')
        else for i := 1 to n do
               if app[i] = 1 then writeln(i)
 end;

begin
  assign(input, fin); reset(input);
  assign(output, fon); rewrite(output);
  initialize;
  solve;
  close(input); close(output)
end.