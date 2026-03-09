; ModuleID = 'dummy_driver.c'
source_filename = "dummy_driver.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [18 x i8] c"Usage: %s <size>\0A\00", align 1, !dbg !0
@.str.3 = private unnamed_addr constant [35 x i8] c"Malloc 3 * sizeof(double) * %d...\0A\00", align 1, !dbg !7
@.str.4 = private unnamed_addr constant [30 x i8] c"Initialisation of size %d...\0A\00", align 1, !dbg !12
@str = private unnamed_addr constant [8 x i8] c"- Start\00", align 1
@str.8 = private unnamed_addr constant [11 x i8] c"Compute...\00", align 1
@str.9 = private unnamed_addr constant [8 x i8] c"Free...\00", align 1
@str.10 = private unnamed_addr constant [8 x i8] c"- Ended\00", align 1
@str.11 = private unnamed_addr constant [20 x i8] c"- size: vector size\00", align 1

; Function Attrs: nounwind sspstrong uwtable
define dso_local noundef i32 @main(i32 noundef %0, ptr noundef readonly captures(none) %1) local_unnamed_addr #0 !dbg !53 {
    #dbg_value(i32 %0, !57, !DIExpression(), !75)
    #dbg_value(ptr %1, !58, !DIExpression(), !75)
  %3 = icmp eq i32 %0, 2, !dbg !76
  br i1 %3, label %7, label %4, !dbg !76

4:                                                ; preds = %2
  %5 = load ptr, ptr %1, align 8, !dbg !78, !tbaa !80
  %6 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str, ptr noundef %5), !dbg !85
  br label %103, !dbg !86

7:                                                ; preds = %2
  %8 = getelementptr inbounds nuw i8, ptr %1, i64 8, !dbg !87
  %9 = load ptr, ptr %8, align 8, !dbg !87, !tbaa !80
    #dbg_value(ptr %9, !88, !DIExpression(), !96)
  %10 = tail call i64 @strtol(ptr noundef nonnull captures(none) %9, ptr noundef null, i32 noundef 10) #8, !dbg !98
  %11 = trunc i64 %10 to i32, !dbg !99
    #dbg_value(i32 %11, !59, !DIExpression(), !75)
  %12 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str), !dbg !100
  %13 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.3, i32 noundef %11), !dbg !101
  %14 = shl i64 %10, 32, !dbg !102
  %15 = ashr exact i64 %14, 29, !dbg !103
  %16 = tail call noalias ptr @malloc(i64 noundef %15) #9, !dbg !104
    #dbg_value(ptr %16, !60, !DIExpression(), !75)
  %17 = tail call noalias ptr @malloc(i64 noundef %15) #9, !dbg !105
    #dbg_value(ptr %17, !61, !DIExpression(), !75)
  %18 = tail call noalias ptr @malloc(i64 noundef %15) #9, !dbg !106
    #dbg_value(ptr %18, !62, !DIExpression(), !75)
  tail call void @srand(i32 noundef 420) #8, !dbg !107
  %19 = tail call i32 (ptr, ...) @printf(ptr noundef nonnull dereferenceable(1) @.str.4, i32 noundef %11), !dbg !108
    #dbg_value(i32 0, !63, !DIExpression(), !109)
  %20 = icmp sgt i32 %11, 0, !dbg !110
  br i1 %20, label %21, label %23, !dbg !112

21:                                               ; preds = %7
  %22 = and i64 %10, 2147483647, !dbg !110
  br label %88, !dbg !112

23:                                               ; preds = %7
  %24 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.8), !dbg !113
    #dbg_value(i32 0, !65, !DIExpression(), !114)
  br label %101, !dbg !115

25:                                               ; preds = %88
  %26 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.8), !dbg !113
    #dbg_value(i32 0, !65, !DIExpression(), !114)
  %27 = and i64 %10, 2147483647, !dbg !116
  %28 = and i64 %10, 1
  %29 = icmp eq i64 %22, 1
  %30 = and i64 %10, 2147483646
  %31 = icmp eq i64 %28, 0
  br label %32, !dbg !115

32:                                               ; preds = %25, %85
  %33 = phi i64 [ 0, %25 ], [ %86, %85 ]
    #dbg_value(i64 %33, !65, !DIExpression(), !114)
  %34 = getelementptr inbounds nuw double, ptr %17, i64 %33, !dbg !117
  %35 = load double, ptr %34, align 8, !dbg !117, !tbaa !118
  %36 = getelementptr inbounds nuw double, ptr %18, i64 %33, !dbg !120
  %37 = load double, ptr %36, align 8, !dbg !120, !tbaa !118
  %38 = fdiv double %35, %37, !dbg !121
  %39 = getelementptr inbounds nuw double, ptr %16, i64 %33, !dbg !122
  %40 = load double, ptr %39, align 8, !dbg !123, !tbaa !118
  %41 = fsub double %40, %38, !dbg !123
  store double %41, ptr %39, align 8, !dbg !123, !tbaa !118
    #dbg_value(i32 0, !67, !DIExpression(), !124)
  br label %42, !dbg !125

42:                                               ; preds = %82, %32
  %43 = phi i64 [ %83, %82 ], [ 0, %32 ]
    #dbg_value(i64 %43, !67, !DIExpression(), !124)
  %44 = getelementptr inbounds nuw double, ptr %16, i64 %43, !dbg !126
  %45 = load double, ptr %44, align 8, !dbg !126, !tbaa !118
  %46 = getelementptr inbounds nuw double, ptr %17, i64 %43, !dbg !127
  %47 = load double, ptr %46, align 8, !dbg !128, !tbaa !118
  %48 = tail call double @llvm.fmuladd.f64(double %45, double %41, double %47), !dbg !128
  store double %48, ptr %46, align 8, !dbg !128, !tbaa !118
    #dbg_value(i32 0, !71, !DIExpression(), !129)
  %49 = load double, ptr %34, align 8, !tbaa !118
  %50 = getelementptr inbounds nuw double, ptr %18, i64 %43
  br i1 %29, label %72, label %51, !dbg !130

51:                                               ; preds = %42, %51
  %52 = phi i64 [ %69, %51 ], [ 0, %42 ]
  %53 = phi i64 [ %70, %51 ], [ 0, %42 ]
    #dbg_value(i64 %52, !71, !DIExpression(), !129)
  %54 = getelementptr inbounds nuw double, ptr %16, i64 %52, !dbg !131
  %55 = load double, ptr %54, align 8, !dbg !131, !tbaa !118
  %56 = fmul double %55, %49, !dbg !134
  %57 = load double, ptr %50, align 8, !dbg !135, !tbaa !118
  %58 = getelementptr inbounds nuw double, ptr %18, i64 %52, !dbg !136
  %59 = load double, ptr %58, align 8, !dbg !137, !tbaa !118
  %60 = tail call double @llvm.fmuladd.f64(double %56, double %57, double %59), !dbg !137
  store double %60, ptr %58, align 8, !dbg !137, !tbaa !118
  %61 = or disjoint i64 %52, 1, !dbg !138
    #dbg_value(i64 %61, !71, !DIExpression(), !129)
  %62 = getelementptr inbounds nuw double, ptr %16, i64 %61, !dbg !131
  %63 = load double, ptr %62, align 8, !dbg !131, !tbaa !118
  %64 = fmul double %63, %49, !dbg !134
  %65 = load double, ptr %50, align 8, !dbg !135, !tbaa !118
  %66 = getelementptr inbounds nuw double, ptr %18, i64 %61, !dbg !136
  %67 = load double, ptr %66, align 8, !dbg !137, !tbaa !118
  %68 = tail call double @llvm.fmuladd.f64(double %64, double %65, double %67), !dbg !137
  store double %68, ptr %66, align 8, !dbg !137, !tbaa !118
  %69 = add nuw nsw i64 %52, 2, !dbg !138
    #dbg_value(i64 %69, !71, !DIExpression(), !129)
  %70 = add i64 %53, 2, !dbg !130
  %71 = icmp eq i64 %70, %30, !dbg !130
  br i1 %71, label %72, label %51, !dbg !130, !llvm.loop !139

72:                                               ; preds = %51, %42
  %73 = phi i64 [ 0, %42 ], [ %69, %51 ]
  br i1 %31, label %82, label %74, !dbg !130

74:                                               ; preds = %72
    #dbg_value(i64 %73, !71, !DIExpression(), !129)
  %75 = getelementptr inbounds nuw double, ptr %16, i64 %73, !dbg !131
  %76 = load double, ptr %75, align 8, !dbg !131, !tbaa !118
  %77 = fmul double %76, %49, !dbg !134
  %78 = load double, ptr %50, align 8, !dbg !135, !tbaa !118
  %79 = getelementptr inbounds nuw double, ptr %18, i64 %73, !dbg !136
  %80 = load double, ptr %79, align 8, !dbg !137, !tbaa !118
  %81 = tail call double @llvm.fmuladd.f64(double %77, double %78, double %80), !dbg !137
  store double %81, ptr %79, align 8, !dbg !137, !tbaa !118
    #dbg_value(i64 %73, !71, !DIExpression(DW_OP_plus_uconst, 1, DW_OP_stack_value), !129)
  br label %82, !dbg !142

82:                                               ; preds = %72, %74
  %83 = add nuw nsw i64 %43, 1, !dbg !142
    #dbg_value(i64 %83, !67, !DIExpression(), !124)
  %84 = icmp eq i64 %83, %27, !dbg !143
  br i1 %84, label %85, label %42, !dbg !125, !llvm.loop !144

85:                                               ; preds = %82
  %86 = add nuw nsw i64 %33, 1, !dbg !146
    #dbg_value(i64 %86, !65, !DIExpression(), !114)
  %87 = icmp eq i64 %86, %27, !dbg !116
  br i1 %87, label %101, label %32, !dbg !115, !llvm.loop !147

88:                                               ; preds = %21, %88
  %89 = phi i64 [ 0, %21 ], [ %99, %88 ]
    #dbg_value(i64 %89, !63, !DIExpression(), !109)
  %90 = tail call i32 @rand() #8, !dbg !149
  %91 = sitofp i32 %90 to double, !dbg !149
  %92 = getelementptr inbounds nuw double, ptr %16, i64 %89, !dbg !151
  store double %91, ptr %92, align 8, !dbg !152, !tbaa !118
  %93 = tail call i32 @rand() #8, !dbg !153
  %94 = sitofp i32 %93 to double, !dbg !153
  %95 = getelementptr inbounds nuw double, ptr %17, i64 %89, !dbg !154
  store double %94, ptr %95, align 8, !dbg !155, !tbaa !118
  %96 = tail call i32 @rand() #8, !dbg !156
  %97 = sitofp i32 %96 to double, !dbg !156
  %98 = getelementptr inbounds nuw double, ptr %18, i64 %89, !dbg !157
  store double %97, ptr %98, align 8, !dbg !158, !tbaa !118
  %99 = add nuw nsw i64 %89, 1, !dbg !159
    #dbg_value(i64 %99, !63, !DIExpression(), !109)
  %100 = icmp eq i64 %99, %22, !dbg !110
  br i1 %100, label %25, label %88, !dbg !112, !llvm.loop !160

101:                                              ; preds = %85, %23
  %102 = tail call i32 @puts(ptr nonnull dereferenceable(1) @str.9), !dbg !162
  tail call void @free(ptr noundef %16) #8, !dbg !163
  tail call void @free(ptr noundef %17) #8, !dbg !164
  tail call void @free(ptr noundef %18) #8, !dbg !165
  br label %103

103:                                              ; preds = %101, %4
  %104 = phi ptr [ @str.10, %101 ], [ @str.11, %4 ]
  %105 = tail call i32 @puts(ptr nonnull dereferenceable(1) %104), !dbg !75
  ret i32 0, !dbg !166
}

; Function Attrs: nofree nounwind
declare !dbg !167 noundef i32 @printf(ptr noundef readonly captures(none), ...) local_unnamed_addr #1

; Function Attrs: mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite)
declare !dbg !172 noalias noundef ptr @malloc(i64 noundef) local_unnamed_addr #2

; Function Attrs: nounwind
declare !dbg !178 void @srand(i32 noundef) local_unnamed_addr #3

; Function Attrs: nounwind
declare !dbg !182 i32 @rand() local_unnamed_addr #3

; Function Attrs: mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare double @llvm.fmuladd.f64(double, double, double) #4

; Function Attrs: mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite)
declare !dbg !185 void @free(ptr allocptr noundef captures(none)) local_unnamed_addr #5

; Function Attrs: mustprogress nocallback nofree nounwind willreturn
declare !dbg !188 i64 @strtol(ptr noundef readonly, ptr noundef captures(none), i32 noundef) local_unnamed_addr #6

; Function Attrs: nofree nounwind
declare noundef i32 @puts(ptr noundef readonly captures(none)) local_unnamed_addr #7

attributes #0 = { nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress nofree nounwind willreturn allockind("alloc,uninitialized") allocsize(0) memory(inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #5 = { mustprogress nounwind willreturn allockind("free") memory(argmem: readwrite, inaccessiblemem: readwrite) "alloc-family"="malloc" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { mustprogress nocallback nofree nounwind willreturn "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { nofree nounwind }
attributes #8 = { nounwind }
attributes #9 = { nounwind allocsize(0) }

!llvm.dbg.cu = !{!17}
!llvm.module.flags = !{!45, !46, !47, !48, !49, !50, !51}
!llvm.ident = !{!52}

!0 = !DIGlobalVariableExpression(var: !1, expr: !DIExpression())
!1 = distinct !DIGlobalVariable(scope: null, file: !2, line: 6, type: !3, isLocal: true, isDefinition: true)
!2 = !DIFile(filename: "dummy_driver.c", directory: "/home/nfond/poc/poc_symbolizer/benchmarks/perf", checksumkind: CSK_MD5, checksum: "017a87f1807274b90b60b312d108b795")
!3 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 144, elements: !5)
!4 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!5 = !{!6}
!6 = !DISubrange(count: 18)
!7 = !DIGlobalVariableExpression(var: !8, expr: !DIExpression())
!8 = distinct !DIGlobalVariable(scope: null, file: !2, line: 15, type: !9, isLocal: true, isDefinition: true)
!9 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 280, elements: !10)
!10 = !{!11}
!11 = !DISubrange(count: 35)
!12 = !DIGlobalVariableExpression(var: !13, expr: !DIExpression())
!13 = distinct !DIGlobalVariable(scope: null, file: !2, line: 23, type: !14, isLocal: true, isDefinition: true)
!14 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 240, elements: !15)
!15 = !{!16}
!16 = !DISubrange(count: 30)
!17 = distinct !DICompileUnit(language: DW_LANG_C11, file: !2, producer: "clang version 21.1.8", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !18, globals: !25, splitDebugInlining: false, nameTableKind: None)
!18 = !{!19, !21, !22, !24}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !20, size: 64)
!20 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!21 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64)
!23 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4, size: 64)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!25 = !{!0, !26, !31, !7, !12, !36, !41, !43}
!26 = !DIGlobalVariableExpression(var: !27, expr: !DIExpression())
!27 = distinct !DIGlobalVariable(scope: null, file: !2, line: 7, type: !28, isLocal: true, isDefinition: true)
!28 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 168, elements: !29)
!29 = !{!30}
!30 = !DISubrange(count: 21)
!31 = !DIGlobalVariableExpression(var: !32, expr: !DIExpression())
!32 = distinct !DIGlobalVariable(scope: null, file: !2, line: 13, type: !33, isLocal: true, isDefinition: true)
!33 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 72, elements: !34)
!34 = !{!35}
!35 = !DISubrange(count: 9)
!36 = !DIGlobalVariableExpression(var: !37, expr: !DIExpression())
!37 = distinct !DIGlobalVariable(scope: null, file: !2, line: 31, type: !38, isLocal: true, isDefinition: true)
!38 = !DICompositeType(tag: DW_TAG_array_type, baseType: !4, size: 96, elements: !39)
!39 = !{!40}
!40 = !DISubrange(count: 12)
!41 = !DIGlobalVariableExpression(var: !42, expr: !DIExpression())
!42 = distinct !DIGlobalVariable(scope: null, file: !2, line: 43, type: !33, isLocal: true, isDefinition: true)
!43 = !DIGlobalVariableExpression(var: !44, expr: !DIExpression())
!44 = distinct !DIGlobalVariable(scope: null, file: !2, line: 49, type: !33, isLocal: true, isDefinition: true)
!45 = !{i32 7, !"Dwarf Version", i32 5}
!46 = !{i32 2, !"Debug Info Version", i32 3}
!47 = !{i32 1, !"wchar_size", i32 4}
!48 = !{i32 8, !"PIC Level", i32 2}
!49 = !{i32 7, !"PIE Level", i32 2}
!50 = !{i32 7, !"uwtable", i32 2}
!51 = !{i32 7, !"debug-info-assignment-tracking", i1 true}
!52 = !{!"clang version 21.1.8"}
!53 = distinct !DISubprogram(name: "main", scope: !2, file: !2, line: 4, type: !54, scopeLine: 4, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !17, retainedNodes: !56)
!54 = !DISubroutineType(types: !55)
!55 = !{!21, !21, !22}
!56 = !{!57, !58, !59, !60, !61, !62, !63, !65, !67, !71}
!57 = !DILocalVariable(name: "argc", arg: 1, scope: !53, file: !2, line: 4, type: !21)
!58 = !DILocalVariable(name: "argv", arg: 2, scope: !53, file: !2, line: 4, type: !22)
!59 = !DILocalVariable(name: "size", scope: !53, file: !2, line: 11, type: !21)
!60 = !DILocalVariable(name: "x", scope: !53, file: !2, line: 17, type: !19)
!61 = !DILocalVariable(name: "y", scope: !53, file: !2, line: 18, type: !19)
!62 = !DILocalVariable(name: "z", scope: !53, file: !2, line: 19, type: !19)
!63 = !DILocalVariable(name: "i", scope: !64, file: !2, line: 25, type: !21)
!64 = distinct !DILexicalBlock(scope: !53, file: !2, line: 25, column: 5)
!65 = !DILocalVariable(name: "i", scope: !66, file: !2, line: 33, type: !21)
!66 = distinct !DILexicalBlock(scope: !53, file: !2, line: 33, column: 5)
!67 = !DILocalVariable(name: "j", scope: !68, file: !2, line: 35, type: !21)
!68 = distinct !DILexicalBlock(scope: !69, file: !2, line: 35, column: 9)
!69 = distinct !DILexicalBlock(scope: !70, file: !2, line: 33, column: 33)
!70 = distinct !DILexicalBlock(scope: !66, file: !2, line: 33, column: 5)
!71 = !DILocalVariable(name: "k", scope: !72, file: !2, line: 37, type: !21)
!72 = distinct !DILexicalBlock(scope: !73, file: !2, line: 37, column: 13)
!73 = distinct !DILexicalBlock(scope: !74, file: !2, line: 35, column: 37)
!74 = distinct !DILexicalBlock(scope: !68, file: !2, line: 35, column: 9)
!75 = !DILocation(line: 0, scope: !53)
!76 = !DILocation(line: 5, column: 13, scope: !77)
!77 = distinct !DILexicalBlock(scope: !53, file: !2, line: 5, column: 8)
!78 = !DILocation(line: 6, column: 38, scope: !79)
!79 = distinct !DILexicalBlock(scope: !77, file: !2, line: 5, column: 19)
!80 = !{!81, !81, i64 0}
!81 = !{!"p1 omnipotent char", !82, i64 0}
!82 = !{!"any pointer", !83, i64 0}
!83 = !{!"omnipotent char", !84, i64 0}
!84 = !{!"Simple C/C++ TBAA"}
!85 = !DILocation(line: 6, column: 9, scope: !79)
!86 = !DILocation(line: 8, column: 9, scope: !79)
!87 = !DILocation(line: 11, column: 21, scope: !53)
!88 = !DILocalVariable(name: "__nptr", arg: 1, scope: !89, file: !90, line: 485, type: !93)
!89 = distinct !DISubprogram(name: "atoi", scope: !90, file: !90, line: 485, type: !91, scopeLine: 486, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !17, retainedNodes: !95)
!90 = !DIFile(filename: "/usr/include/stdlib.h", directory: "", checksumkind: CSK_MD5, checksum: "70a7e0604cc4c4a352d0e5389fa91c9d")
!91 = !DISubroutineType(types: !92)
!92 = !{!21, !93}
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64)
!94 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !4)
!95 = !{!88}
!96 = !DILocation(line: 0, scope: !89, inlinedAt: !97)
!97 = distinct !DILocation(line: 11, column: 16, scope: !53)
!98 = !DILocation(line: 487, column: 16, scope: !89, inlinedAt: !97)
!99 = !DILocation(line: 487, column: 10, scope: !89, inlinedAt: !97)
!100 = !DILocation(line: 13, column: 5, scope: !53)
!101 = !DILocation(line: 15, column: 5, scope: !53)
!102 = !DILocation(line: 17, column: 51, scope: !53)
!103 = !DILocation(line: 17, column: 49, scope: !53)
!104 = !DILocation(line: 17, column: 27, scope: !53)
!105 = !DILocation(line: 18, column: 27, scope: !53)
!106 = !DILocation(line: 19, column: 27, scope: !53)
!107 = !DILocation(line: 21, column: 5, scope: !53)
!108 = !DILocation(line: 23, column: 5, scope: !53)
!109 = !DILocation(line: 0, scope: !64)
!110 = !DILocation(line: 25, column: 21, scope: !111)
!111 = distinct !DILexicalBlock(scope: !64, file: !2, line: 25, column: 5)
!112 = !DILocation(line: 25, column: 5, scope: !64)
!113 = !DILocation(line: 31, column: 5, scope: !53)
!114 = !DILocation(line: 0, scope: !66)
!115 = !DILocation(line: 33, column: 5, scope: !66)
!116 = !DILocation(line: 33, column: 21, scope: !70)
!117 = !DILocation(line: 34, column: 17, scope: !69)
!118 = !{!119, !119, i64 0}
!119 = !{!"double", !83, i64 0}
!120 = !DILocation(line: 34, column: 22, scope: !69)
!121 = !DILocation(line: 34, column: 21, scope: !69)
!122 = !DILocation(line: 34, column: 9, scope: !69)
!123 = !DILocation(line: 34, column: 14, scope: !69)
!124 = !DILocation(line: 0, scope: !68)
!125 = !DILocation(line: 35, column: 9, scope: !68)
!126 = !DILocation(line: 36, column: 21, scope: !73)
!127 = !DILocation(line: 36, column: 13, scope: !73)
!128 = !DILocation(line: 36, column: 18, scope: !73)
!129 = !DILocation(line: 0, scope: !72)
!130 = !DILocation(line: 37, column: 13, scope: !72)
!131 = !DILocation(line: 38, column: 25, scope: !132)
!132 = distinct !DILexicalBlock(scope: !133, file: !2, line: 37, column: 42)
!133 = distinct !DILexicalBlock(scope: !72, file: !2, line: 37, column: 13)
!134 = !DILocation(line: 38, column: 30, scope: !132)
!135 = !DILocation(line: 38, column: 39, scope: !132)
!136 = !DILocation(line: 38, column: 17, scope: !132)
!137 = !DILocation(line: 38, column: 22, scope: !132)
!138 = !DILocation(line: 37, column: 38, scope: !133)
!139 = distinct !{!139, !130, !140, !141}
!140 = !DILocation(line: 39, column: 6, scope: !72)
!141 = !{!"llvm.loop.mustprogress"}
!142 = !DILocation(line: 35, column: 33, scope: !74)
!143 = !DILocation(line: 35, column: 25, scope: !74)
!144 = distinct !{!144, !125, !145, !141}
!145 = !DILocation(line: 40, column: 2, scope: !68)
!146 = !DILocation(line: 33, column: 29, scope: !70)
!147 = distinct !{!147, !115, !148, !141}
!148 = !DILocation(line: 41, column: 5, scope: !66)
!149 = !DILocation(line: 26, column: 16, scope: !150)
!150 = distinct !DILexicalBlock(scope: !111, file: !2, line: 25, column: 33)
!151 = !DILocation(line: 26, column: 9, scope: !150)
!152 = !DILocation(line: 26, column: 14, scope: !150)
!153 = !DILocation(line: 27, column: 16, scope: !150)
!154 = !DILocation(line: 27, column: 9, scope: !150)
!155 = !DILocation(line: 27, column: 14, scope: !150)
!156 = !DILocation(line: 28, column: 16, scope: !150)
!157 = !DILocation(line: 28, column: 9, scope: !150)
!158 = !DILocation(line: 28, column: 14, scope: !150)
!159 = !DILocation(line: 25, column: 29, scope: !111)
!160 = distinct !{!160, !112, !161, !141}
!161 = !DILocation(line: 29, column: 5, scope: !64)
!162 = !DILocation(line: 43, column: 5, scope: !53)
!163 = !DILocation(line: 45, column: 5, scope: !53)
!164 = !DILocation(line: 46, column: 5, scope: !53)
!165 = !DILocation(line: 47, column: 5, scope: !53)
!166 = !DILocation(line: 52, column: 1, scope: !53)
!167 = !DISubprogram(name: "printf", scope: !168, file: !168, line: 370, type: !169, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!168 = !DIFile(filename: "/usr/include/stdio.h", directory: "", checksumkind: CSK_MD5, checksum: "1737dfad03570987edca7e059644f741")
!169 = !DISubroutineType(types: !170)
!170 = !{!21, !171, null}
!171 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !93)
!172 = !DISubprogram(name: "malloc", scope: !90, file: !90, line: 676, type: !173, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!173 = !DISubroutineType(types: !174)
!174 = !{!24, !175}
!175 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !176, line: 18, baseType: !177)
!176 = !DIFile(filename: "/usr/lib/clang/21/include/__stddef_size_t.h", directory: "", checksumkind: CSK_MD5, checksum: "2c44e821a2b1951cde2eb0fb2e656867")
!177 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!178 = !DISubprogram(name: "srand", scope: !90, file: !90, line: 579, type: !179, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!179 = !DISubroutineType(types: !180)
!180 = !{null, !181}
!181 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!182 = !DISubprogram(name: "rand", scope: !90, file: !90, line: 577, type: !183, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!183 = !DISubroutineType(types: !184)
!184 = !{!21}
!185 = !DISubprogram(name: "free", scope: !90, file: !90, line: 691, type: !186, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!186 = !DISubroutineType(types: !187)
!187 = !{null, !24}
!188 = !DISubprogram(name: "strtol", scope: !90, file: !90, line: 181, type: !189, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!189 = !DISubroutineType(types: !190)
!190 = !{!191, !171, !192, !21}
!191 = !DIBasicType(name: "long", size: 64, encoding: DW_ATE_signed)
!192 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !22)
