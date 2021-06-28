; ModuleID = 'main'
source_filename = "main"

@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"

define internal void @main() {
entrypoint:
  %i = alloca i32, align 4
  %i1 = load i32, i32* %i, align 4
  store i32 10, i32* %i, align 4
  store i32 1, i32* %i, align 4
  br label %cond

cond:                                             ; preds = %loop, %entrypoint
  %tmp = load i32, i32* %i, align 4
  %0 = icmp sle i32 %tmp, 3
  %forCond = icmp ne i1 %0, false
  br i1 %forCond, label %loop, label %afterLoop

loop:                                             ; preds = %cond
  %i2 = load i32, i32* %i, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %i2)
  %1 = add i32 %tmp, 1
  store i32 %1, i32* %i, align 4
  br label %cond

afterLoop:                                        ; preds = %cond
  br label %cond3

cond3:                                            ; preds = %loop4, %afterLoop
  %i6 = load i32, i32* %i, align 4
  %tmpSGT = icmp sgt i32 %i6, 0
  %whileCond = icmp ne i1 %tmpSGT, false
  br i1 %whileCond, label %loop4, label %afterLoop5

loop4:                                            ; preds = %cond3
  %i7 = load i32, i32* %i, align 4
  %printf8 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %i7)
  %i9 = load i32, i32* %i, align 4
  %subtmpi = sub i32 %i9, 1
  %i10 = load i32, i32* %i, align 4
  store i32 %subtmpi, i32* %i, align 4
  br label %cond3

afterLoop5:                                       ; preds = %cond3
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)