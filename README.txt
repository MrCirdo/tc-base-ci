
Number of suppressed lines, suppressed chunks, average chunks size:
.                             : 6053 404  14
    lib                       :  260  17  15
        misc                  :  260  17  15
            graph.hh          :    3   1   3
            graph.hxx         :   21   2  10
            scoped-map.hh     :   64   1  64
            scoped-map.hxx    :  155   1 155
            symbol.hxx        :    7   5   1
            test-symbol.cc    :    1   1   1
            unique.hxx        :    8   5   1
            variant.hxx       :    1   1   1
    src                       : 5793 387  14
        ast                   : 1572  70  22
            array-exp.cc      :   26   1  26
            array-exp.hh      :   43   1  43
            array-exp.hxx     :   34   1  34
            assign-exp.cc     :   23   1  23
            assign-exp.hh     :   36   1  36
            assign-exp.hxx    :   23   1  23
            break-exp.cc      :   18   1  18
            break-exp.hh      :   30   1  30
            break-exp.hxx     :   12   1  12
            call-exp.cc       :   24   1  24
            call-exp.hh       :   43   1  43
            call-exp.hxx      :   34   1  34
            default-visitor.hxx:   16   9   1
            escapable.cc      :    8   1   8
            escapable.hh      :   30   1  30
            escapable.hxx     :   12   1  12
            field-var.cc      :   23   1  23
            field-var.hh      :   42   1  42
            field-var.hxx     :   34   1  34
            function-dec.hh   :    2   1   2
            if-exp.cc         :   26   1  26
            if-exp.hh         :   51   1  51
            if-exp.hxx        :   34   1  34
            let-exp.cc        :   23   1  23
            let-exp.hh        :   36   1  36
            let-exp.hxx       :   23   1  23
            method-call-exp.cc:   23   1  23
            method-call-exp.hh:   37   1  37
            method-call-exp.hxx:   23   1  23
            object-exp.cc     :   19   1  19
            object-exp.hh     :   30   1  30
            object-exp.hxx    :   12   1  12
            object-visitor.hxx:    9   5   1
            op-exp.cc         :   19   1  19
            pretty-printer.cc :  294   4  73
            pretty-printer.hh :   30   2  15
            record-exp.cc     :   25   1  25
            record-exp.hh     :   37   1  37
            record-exp.hxx    :   23   1  23
            record-ty.cc      :   22   1  22
            record-ty.hh      :   30   1  30
            record-ty.hxx     :   12   1  12
            seq-exp.cc        :   22   1  22
            seq-exp.hh        :   30   1  30
            seq-exp.hxx       :   12   1  12
            string-exp.cc     :   19   1  19
            string-exp.hh     :   30   1  30
            string-exp.hxx    :   12   1  12
            typable.cc        :    6   1   6
            typable.hh        :   30   1  30
            typable.hxx       :   11   1  11
            type-constructor.cc:    8   1   8
            type-constructor.hh:   30   1  30
            type-constructor.hxx:   11   1  11
        astclone              :  107  35   3
            cloner.cc         :   53  17   3
            cloner.cc~        :   54  18   3
        bind                  :  457  22  20
            binder.cc         :  158   7  22
            binder.hh         :   33   3  11
            binder.hxx        :   45   3  15
            libbind.cc        :   17   1  17
            libbind.hh        :   19   1  19
            renamer.cc        :   44   1  44
            renamer.hh        :    6   2   3
            renamer.hxx       :   43   2  21
            tasks.cc          :   43   1  43
            tasks.hh          :   49   1  49
        callgraph             :    4   1   4
            call-graph-visitor.cc:    4   1   4
        canon                 :  264  12  22
            canon.cc          :   67   6  11
            libcanon.cc       :   20   1  20
            traces.cc         :  177   5  35
        desugar               :  211   5  42
            bounds-checking-visitor.cc:  139   1 139
            bounds-checking-visitor.hh:    7   1   7
            desugar-visitor.cc:   64   2  32
            libdesugar.cc     :    1   1   1
        escapes               :   49   2  24
            escapes-visitor.cc:   35   1  35
            escapes-visitor.hh:   14   1  14
        inlining              :  207   7  29
            inliner.cc        :  119   1 119
            inliner.hh        :    7   2   3
            pruner.cc         :   69   2  34
            pruner.hh         :   12   2   6
        liveness              :  124   4  31
            flowgraph.hxx     :   36   2  18
            interference-graph.cc:   45   1  45
            liveness.cc       :   43   1  43
        object                :  265  63   4
            binder.cc         :   12   2   6
            desugar-visitor.cc:   79  36   2
            libobject.cc      :    8   2   4
            libobject.hh      :    5   1   5
            renamer.cc        :   44   8   5
            tasks.cc          :    6   1   6
            tasks.hh          :    4   1   4
            type-checker.cc   :  107  12   8
        overload              :  159   3  53
            binder.cc         :    4   1   4
            type-checker.cc   :  139   1 139
            type-checker.hh   :   16   1  16
        parse                 :  465  13  35
            parsetiger.yy     :  432   7  61
            scantiger.ll      :   18   3   6
            tasks.cc          :    2   1   2
            tiger-parser.cc   :   13   2   6
        target                :  727  43  16
            arm               :   97  10   9
                arm-assembly.cc:    7   2   3
                arm-codegen.cc:   45   4  11
                call.brg      :    9   1   9
                epilogue.cc   :   33   1  33
                move.brg      :    3   2   1
            ia32              :  187  10  18
                call.brg      :    9   1   9
                epilogue.cc   :   76   1  76
                gas-assembly.cc:   11   2   5
                gas-codegen.cc:   88   4  22
                move.brg      :    3   2   1
            mips              :  443  23  19
                call.brg      :   10   1  10
                epilogue.cc   :   76   1  76
                move.brg      :    3   2   1
                runtime.s     :  214   6  35
                spim-assembly.cc:   51   9   5
                spim-codegen.cc:   89   4  22
        temp                  :   57  16   3
            identifier.hxx    :   57  16   3
        translate             :  304  38   8
            exp.cc            :   47   6   7
            level.cc          :    3   1   3
            translation.cc    :  148  10  14
            translation.hh    :    6   1   6
            translator.cc     :  100  20   5
        tree                  :   54   1  54
            fragment.cc       :   54   1  54
        type                  :  767  52  14
            array.cc          :    5   1   5
            array.hh          :   20   1  20
            array.hxx         :   10   1  10
            builtin-types.cc  :   52   2  26
            builtin-types.hh  :   76   1  76
            class.cc          :   67   7   9
            class.hh          :    6   1   6
            function.cc       :   39   1  39
            function.hh       :    2   1   2
            method.cc         :   11   1  11
            method.hh         :    2   1   2
            named.cc          :   51   2  25
            named.hxx         :    2   1   2
            record.cc         :   38   3  12
            record.hh         :    1   1   1
            type-checker.cc   :  365  20  18
            type-checker.hh   :   13   2   6
            type-checker.hxx  :    5   3   1
            type.hxx          :    2   2   1
