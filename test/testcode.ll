; ModuleID = 'testcode.c'
source_filename = "testcode.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@g = common global i32 0, align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  store i32 0, i32* %retval, align 4
  ret i32 0
}

; Function Attrs: nounwind uwtable
define i32 @erk(i32 %a, i32 %b) #0 {
entry:
  %a.addr = alloca i32, align 4
  %b.addr = alloca i32, align 4
  %i = alloca i32, align 4
  %x = alloca i32, align 4
  %ret = alloca i32, align 4
  store i32 %a, i32* %a.addr, align 4
  store i32 %b, i32* %b.addr, align 4
  %0 = load i32, i32* @g, align 4
  store i32 %0, i32* %x, align 4
  store i32 0, i32* %ret, align 4
  %1 = load i32, i32* %ret, align 4
  %tobool = icmp ne i32 %1, 0
  br i1 %tobool, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %x, align 4
  %3 = load i32, i32* %ret, align 4
  %sub = sub nsw i32 %2, %3
  store i32 %sub, i32* %x, align 4
  br label %if.end

if.else:                                          ; preds = %entry
  %4 = load i32, i32* %x, align 4
  %5 = load i32, i32* %ret, align 4
  %add = add nsw i32 %4, %5
  store i32 %add, i32* %x, align 4
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  store i32 5, i32* %ret, align 4
  %6 = load i32, i32* %b.addr, align 4
  ret i32 %6
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (http://llvm.org/git/clang.git 12dcbf43701c142e8313d322c14b53a6c2957826) (http://llvm.org/git/llvm.git 9f072db19bc4f674b85c936c7983212c4034030d)"}
