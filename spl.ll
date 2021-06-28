; ModuleID = 'main'
source_filename = "main"

@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"
@.str.2 = constant [4 x i8] c"%d\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"
@.str.4 = constant [4 x i8] c"%d\0A\00"
@.str.5 = constant [4 x i8] c"%c\0A\00"
@.str.6 = constant [5 x i8] c"%lf\0A\00"
@.str.7 = constant [5 x i8] c"%lf\0A\00"

define internal void @main() {
entrypoint:
  %r = alloca double, align 8
  %c = alloca i8, align 1
  %k = alloca i32, align 4
  %f = alloca i32, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 3)
  %k1 = load i32, i32* %k, align 4
  store i32 0, i32* %k, align 4
  br label %cond

cond:                                             ; preds = %loop, %entrypoint
  %k2 = load i32, i32* %k, align 4
  %tmpSLT = icmp slt i32 %k2, 5
  %whileCond = icmp ne i1 %tmpSLT, false
  br i1 %whileCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %k3 = load i32, i32* %k, align 4
  %printf4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %k3)
  %k5 = load i32, i32* %k, align 4
  %k6 = load i32, i32* %k, align 4
  %addtmpi = add i32 %k6, 1
  store i32 %addtmpi, i32* %k, align 4
  br label %cond

afterLoop:                                        ; preds = %cond
  %k7 = load i32, i32* %k, align 4
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %k7)
  %f9 = load i32, i32* %f, align 4
  %k10 = load i32, i32* %k, align 4
  %addtmpi11 = add i32 %k10, 50
  %k12 = load i32, i32* %k, align 4
  %tmpDiv = sdiv i32 10, %k12
  %subtmpi = sub i32 %addtmpi11, %tmpDiv
  %addtmpi13 = add i32 %subtmpi, 3
  store i32 %addtmpi13, i32* %f, align 4
  %f14 = load i32, i32* %f, align 4
  %printf15 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %f14)
  %f16 = load i32, i32* %f, align 4
  %k17 = load i32, i32* %k, align 4
  %calltmp = call i32 @go(i32 5, i32 %k17)
  store i32 %calltmp, i32* %f, align 4
  %f18 = load i32, i32* %f, align 4
  %printf19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i32 %f18)
  %c20 = load i8, i8* %c, align 1
  store i8 72, i8* %c, align 1
  %c21 = load i8, i8* %c, align 1
  %printf22 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i32 0, i32 0), i8 %c21)
  %r23 = load double, double* %r, align 8
  store double 3.000000e-03, double* %r, align 8
  %r24 = load double, double* %r, align 8
  %printf25 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i32 0, i32 0), double %r24)
  %r26 = load double, double* %r, align 8
  %r27 = load double, double* %r, align 8
  %addtmpf = fadd double %r27, 1.100000e+00
  store double %addtmpf, double* %r, align 8
  %r28 = load double, double* %r, align 8
  %printf29 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i32 0, i32 0), double %r28)
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal i32 @go(i32 %0, i32 %1) {
entrypoint:
  %go = alloca i32, align 4
  %a = alloca i32, align 4
  %b = alloca i32, align 4
  store i32 %0, i32* %b, align 4
  store i32 %1, i32* %a, align 4
  %a1 = load i32, i32* %a, align 4
  %tmpSGT = icmp sgt i32 %a1, 0
  %ifCond = icmp ne i1 %tmpSGT, false
  br i1 %ifCond, label %then, label %else

then:                                             ; preds = %entrypoint
  %go2 = load i32, i32* %go, align 4
  %a3 = load i32, i32* %a, align 4
  %multmpi = mul i32 %a3, 2
  store i32 %multmpi, i32* %go, align 4
  br label %merge

else:                                             ; preds = %entrypoint
  %go4 = load i32, i32* %go, align 4
  store i32 1, i32* %go, align 4
  br label %merge

merge:                                            ; preds = %else, %then
  %go5 = load i32, i32* %go, align 4
  ret i32 %go5
}




