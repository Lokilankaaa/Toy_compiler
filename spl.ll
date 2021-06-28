; ModuleID = 'main'
source_filename = "main"

@0 = private unnamed_addr constant [3 x i8] c"%c\00", align 1
@.str = constant [4 x i8] c"%c\0A\00"
@1 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = constant [4 x i8] c"%d\0A\00"
@2 = private unnamed_addr constant [4 x i8] c"%lf\00", align 1
@.str.2 = constant [5 x i8] c"%lf\0A\00"
@3 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.3 = constant [4 x i8] c"%d\0A\00"

define internal void @main() {
entrypoint:
  %b = alloca i1, align 1
  %c = alloca i8, align 1
  %r = alloca double, align 8
  %i = alloca i32, align 4
  %c1 = load i8, i8* %c, align 1
  %scanf = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @0, i32 0, i32 0), i8* %c)
  %c2 = load i8, i8* %c, align 1
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i8 %c2)
  %i3 = load i32, i32* %i, align 4
  %scanf4 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @1, i32 0, i32 0), i32* %i)
  %i5 = load i32, i32* %i, align 4
  %printf6 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %i5)
  %r7 = load double, double* %r, align 8
  %scanf8 = call i32 (...) @scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @2, i32 0, i32 0), double* %r)
  %r9 = load double, double* %r, align 8
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), double %r9)
  %b11 = load i1, i1* %b, align 1
  %scanf12 = call i32 (...) @scanf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @3, i32 0, i32 0), i1* %b)
  %b13 = load i1, i1* %b, align 1
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i1 %b13)
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)