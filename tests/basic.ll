; ModuleID = 'basic.c'
source_filename = "basic.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: noinline nounwind uwtable
define dso_local i32 @main() #0 {
entry:
  %retval = alloca i32, align 4
  %b = alloca i32, align 4
  %f = alloca i32, align 4
  %a = alloca i32*, align 8
  %c = alloca i32, align 4
  %d = alloca i32*, align 8
  store i32 0, i32* %retval, align 4
  store i32 1, i32* %b, align 4
  store i32 2, i32* %f, align 4
  store i32* %b, i32** %a, align 8
  %0 = load i32, i32* %b, align 4
  store i32 %0, i32* %c, align 4
  %1 = load i32*, i32** %a, align 8
  store i32* %1, i32** %d, align 8
  %2 = load i32, i32* %f, align 4
  %3 = load i32*, i32** %a, align 8
  store i32 %2, i32* %3, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"clang version 11.0.1 (https://github.com/llvm/llvm-project.git 43ff75f2c3feef64f9d73328230d34dac8832a91)"}
