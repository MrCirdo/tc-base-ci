; ModuleID = 'src/llvmtranslate/tiger-runtime.c'
target datalayout = "e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128"
target triple = "i386-pc-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i32, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i32, i32, [40 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }

@.str = private unnamed_addr constant [29 x i8] c"chr: character out of range\0A\00", align 1
@stderr = external global %struct._IO_FILE*, align 4
@consts = internal global [512 x i8] zeroinitializer, align 1
@.str.1 = private unnamed_addr constant [36 x i8] c"substring: arguments out of bounds\0A\00", align 1
@stdin = external global %struct._IO_FILE*, align 4
@.str.2 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@stdout = external global %struct._IO_FILE*, align 4

; Function Attrs: nounwind
define i32* @tc_init_array(i32 %size, i32 %elt) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %arr = alloca i32*, align 4
  %i = alloca i32, align 4
  store i32 %size, i32* %1, align 4
  store i32 %elt, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = mul i32 %3, 4
  %5 = call noalias i8* @malloc(i32 %4) #4
  %6 = bitcast i8* %5 to i32*
  store i32* %6, i32** %arr, align 4
  store i32 0, i32* %i, align 4
  br label %7

; <label>:7                                       ; preds = %16, %0
  %8 = load i32, i32* %i, align 4
  %9 = load i32, i32* %1, align 4
  %10 = icmp ult i32 %8, %9
  br i1 %10, label %11, label %19

; <label>:11                                      ; preds = %7
  %12 = load i32, i32* %2, align 4
  %13 = load i32, i32* %i, align 4
  %14 = load i32*, i32** %arr, align 4
  %15 = getelementptr inbounds i32, i32* %14, i32 %13
  store i32 %12, i32* %15, align 4
  br label %16

; <label>:16                                      ; preds = %11
  %17 = load i32, i32* %i, align 4
  %18 = add i32 %17, 1
  store i32 %18, i32* %i, align 4
  br label %7

; <label>:19                                      ; preds = %7
  %20 = load i32*, i32** %arr, align 4
  ret i32* %20
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i32) #0

; Function Attrs: nounwind
define i32 @tc_not(i32 %i) #0 {
  %1 = alloca i32, align 4
  store i32 %i, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = icmp ne i32 %2, 0
  %4 = xor i1 %3, true
  %5 = zext i1 %4 to i32
  ret i32 %5
}

; Function Attrs: nounwind
define void @tc_exit(i32 %status) #0 {
  %1 = alloca i32, align 4
  store i32 %status, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  call void @exit(i32 %2) #5
  unreachable
                                                  ; No predecessors!
  ret void
}

; Function Attrs: noreturn nounwind
declare void @exit(i32) #1

; Function Attrs: nounwind
define i8* @tc_chr(i32 %i) #0 {
  %1 = alloca i32, align 4
  store i32 %i, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = icmp sle i32 0, %2
  br i1 %3, label %4, label %7

; <label>:4                                       ; preds = %0
  %5 = load i32, i32* %1, align 4
  %6 = icmp sle i32 %5, 255
  br i1 %6, label %10, label %7

; <label>:7                                       ; preds = %4, %0
  %8 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 4
  %9 = call i32 @fputs(i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str, i32 0, i32 0), %struct._IO_FILE* %8)
  call void @exit(i32 120) #5
  unreachable

; <label>:10                                      ; preds = %4
  %11 = load i32, i32* %1, align 4
  %12 = mul nsw i32 %11, 2
  %13 = getelementptr inbounds i8, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @consts, i32 0, i32 0), i32 %12
  ret i8* %13
}

declare i32 @fputs(i8*, %struct._IO_FILE*) #2

; Function Attrs: nounwind
define i8* @tc_concat(i8* %a, i8* %b) #0 {
  %1 = alloca i8*, align 4
  %2 = alloca i8*, align 4
  %3 = alloca i8*, align 4
  %len_a = alloca i32, align 4
  %len_b = alloca i32, align 4
  %i = alloca i32, align 4
  %n = alloca i32, align 4
  %t = alloca i8*, align 4
  store i8* %a, i8** %2, align 4
  store i8* %b, i8** %3, align 4
  %4 = load i8*, i8** %2, align 4
  %5 = call i32 @strlen(i8* %4) #6
  store i32 %5, i32* %len_a, align 4
  %6 = load i8*, i8** %3, align 4
  %7 = call i32 @strlen(i8* %6) #6
  store i32 %7, i32* %len_b, align 4
  %8 = load i32, i32* %len_a, align 4
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %10, label %12

; <label>:10                                      ; preds = %0
  %11 = load i8*, i8** %3, align 4
  store i8* %11, i8** %1, align 4
  br label %62

; <label>:12                                      ; preds = %0
  %13 = load i32, i32* %len_b, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %15, label %17

; <label>:15                                      ; preds = %12
  %16 = load i8*, i8** %2, align 4
  store i8* %16, i8** %1, align 4
  br label %62

; <label>:17                                      ; preds = %12
  store i32 0, i32* %i, align 4
  %18 = load i32, i32* %len_a, align 4
  %19 = load i32, i32* %len_b, align 4
  %20 = add i32 %18, %19
  store i32 %20, i32* %n, align 4
  %21 = load i32, i32* %n, align 4
  %22 = add nsw i32 %21, 1
  %23 = call noalias i8* @malloc(i32 %22) #4
  store i8* %23, i8** %t, align 4
  store i32 0, i32* %i, align 4
  br label %24

; <label>:24                                      ; preds = %36, %17
  %25 = load i32, i32* %i, align 4
  %26 = load i32, i32* %len_a, align 4
  %27 = icmp ult i32 %25, %26
  br i1 %27, label %28, label %39

; <label>:28                                      ; preds = %24
  %29 = load i32, i32* %i, align 4
  %30 = load i8*, i8** %2, align 4
  %31 = getelementptr inbounds i8, i8* %30, i32 %29
  %32 = load i8, i8* %31, align 1
  %33 = load i32, i32* %i, align 4
  %34 = load i8*, i8** %t, align 4
  %35 = getelementptr inbounds i8, i8* %34, i32 %33
  store i8 %32, i8* %35, align 1
  br label %36

; <label>:36                                      ; preds = %28
  %37 = load i32, i32* %i, align 4
  %38 = add nsw i32 %37, 1
  store i32 %38, i32* %i, align 4
  br label %24

; <label>:39                                      ; preds = %24
  store i32 0, i32* %i, align 4
  br label %40

; <label>:40                                      ; preds = %54, %39
  %41 = load i32, i32* %i, align 4
  %42 = load i32, i32* %len_b, align 4
  %43 = icmp ult i32 %41, %42
  br i1 %43, label %44, label %57

; <label>:44                                      ; preds = %40
  %45 = load i32, i32* %i, align 4
  %46 = load i8*, i8** %3, align 4
  %47 = getelementptr inbounds i8, i8* %46, i32 %45
  %48 = load i8, i8* %47, align 1
  %49 = load i32, i32* %i, align 4
  %50 = load i32, i32* %len_a, align 4
  %51 = add i32 %49, %50
  %52 = load i8*, i8** %t, align 4
  %53 = getelementptr inbounds i8, i8* %52, i32 %51
  store i8 %48, i8* %53, align 1
  br label %54

; <label>:54                                      ; preds = %44
  %55 = load i32, i32* %i, align 4
  %56 = add nsw i32 %55, 1
  store i32 %56, i32* %i, align 4
  br label %40

; <label>:57                                      ; preds = %40
  %58 = load i32, i32* %n, align 4
  %59 = load i8*, i8** %t, align 4
  %60 = getelementptr inbounds i8, i8* %59, i32 %58
  store i8 0, i8* %60, align 1
  %61 = load i8*, i8** %t, align 4
  store i8* %61, i8** %1, align 4
  br label %62

; <label>:62                                      ; preds = %57, %15, %10
  %63 = load i8*, i8** %1, align 4
  ret i8* %63
}

; Function Attrs: nounwind readonly
declare i32 @strlen(i8*) #3

; Function Attrs: nounwind
define i32 @tc_ord(i8* %s) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i8*, align 4
  %len = alloca i32, align 4
  store i8* %s, i8** %2, align 4
  %3 = load i8*, i8** %2, align 4
  %4 = call i32 @strlen(i8* %3) #6
  store i32 %4, i32* %len, align 4
  %5 = load i32, i32* %len, align 4
  %6 = icmp eq i32 %5, 0
  br i1 %6, label %7, label %8

; <label>:7                                       ; preds = %0
  store i32 -1, i32* %1, align 4
  br label %13

; <label>:8                                       ; preds = %0
  %9 = load i8*, i8** %2, align 4
  %10 = getelementptr inbounds i8, i8* %9, i32 0
  %11 = load i8, i8* %10, align 1
  %12 = sext i8 %11 to i32
  store i32 %12, i32* %1, align 4
  br label %13

; <label>:13                                      ; preds = %8, %7
  %14 = load i32, i32* %1, align 4
  ret i32 %14
}

; Function Attrs: nounwind
define i32 @tc_size(i8* %s) #0 {
  %1 = alloca i8*, align 4
  store i8* %s, i8** %1, align 4
  %2 = load i8*, i8** %1, align 4
  %3 = call i32 @strlen(i8* %2) #6
  ret i32 %3
}

; Function Attrs: nounwind
define i8* @tc_substring(i8* %s, i32 %first, i32 %n) #0 {
  %1 = alloca i8*, align 4
  %2 = alloca i8*, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %len = alloca i32, align 4
  %t = alloca i8*, align 4
  %i = alloca i32, align 4
  store i8* %s, i8** %2, align 4
  store i32 %first, i32* %3, align 4
  store i32 %n, i32* %4, align 4
  %5 = load i8*, i8** %2, align 4
  %6 = call i32 @strlen(i8* %5) #6
  store i32 %6, i32* %len, align 4
  %7 = load i32, i32* %3, align 4
  %8 = icmp sle i32 0, %7
  br i1 %8, label %9, label %18

; <label>:9                                       ; preds = %0
  %10 = load i32, i32* %4, align 4
  %11 = icmp sle i32 0, %10
  br i1 %11, label %12, label %18

; <label>:12                                      ; preds = %9
  %13 = load i32, i32* %3, align 4
  %14 = load i32, i32* %4, align 4
  %15 = add nsw i32 %13, %14
  %16 = load i32, i32* %len, align 4
  %17 = icmp ule i32 %15, %16
  br i1 %17, label %21, label %18

; <label>:18                                      ; preds = %12, %9, %0
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 4
  %20 = call i32 @fputs(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.1, i32 0, i32 0), %struct._IO_FILE* %19)
  call void @exit(i32 120) #5
  unreachable

; <label>:21                                      ; preds = %12
  %22 = load i32, i32* %4, align 4
  %23 = icmp eq i32 %22, 1
  br i1 %23, label %24, label %32

; <label>:24                                      ; preds = %21
  %25 = load i32, i32* %3, align 4
  %26 = load i8*, i8** %2, align 4
  %27 = getelementptr inbounds i8, i8* %26, i32 %25
  %28 = load i8, i8* %27, align 1
  %29 = sext i8 %28 to i32
  %30 = mul nsw i32 %29, 2
  %31 = getelementptr inbounds i8, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @consts, i32 0, i32 0), i32 %30
  store i8* %31, i8** %1, align 4
  br label %58

; <label>:32                                      ; preds = %21
  %33 = load i32, i32* %4, align 4
  %34 = add nsw i32 %33, 1
  %35 = call noalias i8* @malloc(i32 %34) #4
  store i8* %35, i8** %t, align 4
  store i32 0, i32* %i, align 4
  br label %36

; <label>:36                                      ; preds = %50, %32
  %37 = load i32, i32* %i, align 4
  %38 = load i32, i32* %4, align 4
  %39 = icmp slt i32 %37, %38
  br i1 %39, label %40, label %53

; <label>:40                                      ; preds = %36
  %41 = load i32, i32* %3, align 4
  %42 = load i32, i32* %i, align 4
  %43 = add nsw i32 %41, %42
  %44 = load i8*, i8** %2, align 4
  %45 = getelementptr inbounds i8, i8* %44, i32 %43
  %46 = load i8, i8* %45, align 1
  %47 = load i32, i32* %i, align 4
  %48 = load i8*, i8** %t, align 4
  %49 = getelementptr inbounds i8, i8* %48, i32 %47
  store i8 %46, i8* %49, align 1
  br label %50

; <label>:50                                      ; preds = %40
  %51 = load i32, i32* %i, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %i, align 4
  br label %36

; <label>:53                                      ; preds = %36
  %54 = load i32, i32* %4, align 4
  %55 = load i8*, i8** %t, align 4
  %56 = getelementptr inbounds i8, i8* %55, i32 %54
  store i8 0, i8* %56, align 1
  %57 = load i8*, i8** %t, align 4
  store i8* %57, i8** %1, align 4
  br label %58

; <label>:58                                      ; preds = %53, %24
  %59 = load i8*, i8** %1, align 4
  ret i8* %59
}

; Function Attrs: nounwind
define i32 @tc_strcmp(i8* %lhs, i8* %rhs) #0 {
  %1 = alloca i8*, align 4
  %2 = alloca i8*, align 4
  store i8* %lhs, i8** %1, align 4
  store i8* %rhs, i8** %2, align 4
  %3 = load i8*, i8** %1, align 4
  %4 = load i8*, i8** %2, align 4
  %5 = call i32 @strcmp(i8* %3, i8* %4) #6
  ret i32 %5
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

; Function Attrs: nounwind
define i32 @tc_streq(i8* %lhs, i8* %rhs) #0 {
  %1 = alloca i8*, align 4
  %2 = alloca i8*, align 4
  store i8* %lhs, i8** %1, align 4
  store i8* %rhs, i8** %2, align 4
  %3 = load i8*, i8** %1, align 4
  %4 = load i8*, i8** %2, align 4
  %5 = call i32 @strcmp(i8* %3, i8* %4) #6
  %6 = icmp eq i32 %5, 0
  %7 = zext i1 %6 to i32
  ret i32 %7
}

; Function Attrs: nounwind
define i8* @tc_getchar() #0 {
  %1 = alloca i8*, align 4
  %i = alloca i32, align 4
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 4
  %3 = call i32 @_IO_getc(%struct._IO_FILE* %2)
  store i32 %3, i32* %i, align 4
  %4 = load i32, i32* %i, align 4
  %5 = icmp eq i32 %4, -1
  br i1 %5, label %6, label %7

; <label>:6                                       ; preds = %0
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.2, i32 0, i32 0), i8** %1, align 4
  br label %11

; <label>:7                                       ; preds = %0
  %8 = load i32, i32* %i, align 4
  %9 = mul nsw i32 %8, 2
  %10 = getelementptr inbounds i8, i8* getelementptr inbounds ([512 x i8], [512 x i8]* @consts, i32 0, i32 0), i32 %9
  store i8* %10, i8** %1, align 4
  br label %11

; <label>:11                                      ; preds = %7, %6
  %12 = load i8*, i8** %1, align 4
  ret i8* %12
}

declare i32 @_IO_getc(%struct._IO_FILE*) #2

; Function Attrs: nounwind
define void @tc_print(i8* %s) #0 {
  %1 = alloca i8*, align 4
  store i8* %s, i8** %1, align 4
  %2 = load i8*, i8** %1, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i8* %2)
  ret void
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: nounwind
define void @tc_print_err(i8* %s) #0 {
  %1 = alloca i8*, align 4
  store i8* %s, i8** %1, align 4
  %2 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 4
  %3 = load i8*, i8** %1, align 4
  %4 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %2, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i8* %3)
  ret void
}

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind
define void @tc_print_int(i32 %i) #0 {
  %1 = alloca i32, align 4
  store i32 %i, i32* %1, align 4
  %2 = load i32, i32* %1, align 4
  %3 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0), i32 %2)
  ret void
}

; Function Attrs: nounwind
define void @tc_flush() #0 {
  %1 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 4
  %2 = call i32 @fflush(%struct._IO_FILE* %1)
  ret void
}

declare i32 @fflush(%struct._IO_FILE*) #2

; Function Attrs: nounwind
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %i = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 0, i32* %i, align 4
  br label %2

; <label>:2                                       ; preds = %14, %0
  %3 = load i32, i32* %i, align 4
  %4 = icmp slt i32 %3, 512
  br i1 %4, label %5, label %17

; <label>:5                                       ; preds = %2
  %6 = load i32, i32* %i, align 4
  %7 = sdiv i32 %6, 2
  %8 = trunc i32 %7 to i8
  %9 = load i32, i32* %i, align 4
  %10 = getelementptr inbounds [512 x i8], [512 x i8]* @consts, i32 0, i32 %9
  store i8 %8, i8* %10, align 1
  %11 = load i32, i32* %i, align 4
  %12 = add nsw i32 %11, 1
  %13 = getelementptr inbounds [512 x i8], [512 x i8]* @consts, i32 0, i32 %12
  store i8 0, i8* %13, align 1
  br label %14

; <label>:14                                      ; preds = %5
  %15 = load i32, i32* %i, align 4
  %16 = add nsw i32 %15, 2
  store i32 %16, i32* %i, align 4
  br label %2

; <label>:17                                      ; preds = %2
  call void @tc_main(i32 0)
  ret i32 0
}

declare void @tc_main(i32) #2

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="pentium4" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }
attributes #6 = { nounwind readonly }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.0-2 (tags/RELEASE_380/final)"}
