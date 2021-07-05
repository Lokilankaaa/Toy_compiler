; ModuleID = 'main'
source_filename = "main"

define internal void @main() {
entrypoint:
  %i = alloca i32, align 4
  %i1 = load i32, i32* %i, align 4
  store i32 6, i32* %i, align 4
  ret void
}

declare i32 @printf(i8*, ...)

declare i32 @scanf(...)