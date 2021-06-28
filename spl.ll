; ModuleID = 'main'
source_filename = "main"

%0 = type { i32, i32 }

@.str = constant [4 x i8] c"%d\0A\00"
@.str.1 = constant [4 x i8] c"%d\0A\00"
@.str.2 = constant [4 x i8] c"%d\0A\00"

define internal void @main() {
entrypoint:
  %m = alloca %0, align 8
  %i = alloca i32, align 4
  %m1 = load %0, %0* %m, align 4
  %0 = getelementptr inbounds %0, %0* %m, i32 0, i32 0
  store i32 10, i32* %0, align 4
  %m2 = load %0, %0* %m, align 4
  %1 = getelementptr inbounds %0, %0* %m, i32 0, i32 1
  store i32 160, i32* %1, align 4
  %m3 = load %0, %0* %m, align 4
  %m4 = load %0, %0* %m, align 4
  %2 = getelementptr inbounds %0, %0* %m, i32 0, i32 0
  %recRef = load i32, i32* %2, align 4
  %addtmpi = add i32 %recRef, 3
  %i5 = load i32, i32* %i, align 4
  store i32 %addtmpi, i32* %i, align 4
  %i6 = load i32, i32* %i, align 4
  %printf = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i32 0, i32 0), i32 %i6)
  %m7 = load %0, %0* %m, align 4
  %m8 = load %0, %0* %m, align 4
  %3 = getelementptr inbounds %0, %0* %m, i32 0, i32 0
  %recRef9 = load i32, i32* %3, align 4
  %printf10 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 %recRef9)
  %m11 = load %0, %0* %m, align 4
  %m12 = load %0, %0* %m, align 4
  %4 = getelementptr inbounds %0, %0* %m, i32 0, i32 1
  %recRef13 = load i32, i32* %4, align 4
  %printf14 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.2, i32 0, i32 0), i32 %recRef13)
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)