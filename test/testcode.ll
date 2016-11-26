; ModuleID = '<stdin>'
source_filename = "testcode.c"
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@.str = private unnamed_addr constant [20 x i8] c"This is foo! %d/%d\0A\00", align 1
@.str.1 = private unnamed_addr constant [15 x i8] c"This is main!\0A\00", align 1
@.str.2 = private unnamed_addr constant [13 x i8] c"Foo says %d\0A\00", align 1
@.str.3 = private unnamed_addr constant [6 x i8] c"Bye!\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @foo(i32 %n) #0 {
entry:
  br label %for.cond

for.cond:                                         ; preds = %for.inc, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %inc, %for.inc ]
  %cmp = icmp slt i32 %i.0, %n
  br i1 %cmp, label %for.body, label %for.end

for.body:                                         ; preds = %for.cond
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i32 %i.0, i32 %n)
  br label %for.inc

for.inc:                                          ; preds = %for.body
  %inc = add nsw i32 %i.0, 1
  br label %for.cond

for.end:                                          ; preds = %for.cond
  %cmp1 = icmp eq i32 %n, 0
  br i1 %cmp1, label %if.then, label %if.else

if.then:                                          ; preds = %for.end
  br label %return

if.else:                                          ; preds = %for.end
  %sub = sub nsw i32 %n, 1
  %call2 = call i32 @foo(i32 %sub)
  %add = add nsw i32 1, %call2
  br label %return

return:                                           ; preds = %if.else, %if.then
  %retval.0 = phi i32 [ 0, %if.then ], [ %add, %if.else ]
  ret i32 %retval.0
}

declare i32 @printf(i8*, ...) #1

; Function Attrs: nounwind uwtable
define void @bar(i32 %b, i32 %g, i32 %k) #0 {
entry:
  %add = add nsw i32 1, %b
  ret void
}

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %call = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.1, i32 0, i32 0))
  %sub = sub nsw i32 1, 2
  call void @bar(i32 %sub, i32 1, i32 2)
  %mul = mul nsw i32 2, 2
  %add = add nsw i32 1, %mul
  %call1 = call i32 @foo(i32 %add)
  %call2 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.2, i32 0, i32 0), i32 %call1)
  %call3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.3, i32 0, i32 0))
  ret i32 0
}

attributes #0 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = !{!"clang version 4.0.0 (http://llvm.org/git/clang.git 35613b69716800cec4003c5a29239241fb1012c3) (http://llvm.org/git/llvm.git d89ff9a37ef34c773011bc6113b36a1f6db2807c)"}
