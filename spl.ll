; ModuleID = 'main'
source_filename = "main"

@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"
@.str.2 = constant [4 x i8] c"%d\0A\00"
@.str.3 = constant [4 x i8] c"%d\0A\00"

define internal void @main() {
entrypoint:
  %c = alloca i32, align 4
  %i = alloca i32, align 4
  %i1 = load i32, i32* %i, align 4
  store i32 0, i32* %i, align 4
  %c2 = load i32, i32* %c, align 4
  store i32 0, i32* %c, align 4
  %i3 = load i32, i32* %i, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %i3)
  %c4 = load i32, i32* %c, align 4
  %printf5 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %c4)
  %i6 = load i32, i32* %i, align 4
  %c7 = load i32, i32* %c, align 4
  %calltmp = call i32 @go(i32 %i6, i32 %c7)
  %i8 = load i32, i32* %i, align 4
  %printf9 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %i8)
  %c10 = load i32, i32* %c, align 4
  %printf11 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i32 %c10)
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)

define internal i32 @go(i32 nonnull %0, i32* %1) {
entrypoint:
  %go = alloca i32, align 4
  %a = alloca i32, align 4
  store i32 %0, i32* %a, align 4
  %b = getelementptr i32, i32* %1, i32 0
  %a1 = load i32, i32* %a, align 4
  %addtmpi = add i32 %a1, 1
  %a2 = load i32, i32* %a, align 4
  store i32 %addtmpi, i32* %a, align 4
  %b3 = load i32, i32* %b, align 4
  %subtmpi = sub i32 %b3, 1
  %b4 = load i32, i32* %b, align 4
  store i32 %subtmpi, i32* %b, align 4
  %go5 = load i32, i32* %go, align 4
  ret i32 %go5
}