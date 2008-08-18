IN: compiler.tree.tuple-unboxing.tests
USING: tools.test compiler.tree.tuple-unboxing compiler.tree
compiler.tree.builder compiler.tree.normalization
compiler.tree.propagation compiler.tree.cleanup
compiler.tree.escape-analysis compiler.tree.tuple-unboxing
compiler.tree.checker compiler.tree.def-use kernel accessors
sequences math math.private sorting math.order binary-search
sequences.private slots.private ;

\ unbox-tuples must-infer

: test-unboxing ( quot -- )
    build-tree
    normalize
    propagate
    cleanup
    escape-analysis
    unbox-tuples
    check-nodes ;

TUPLE: cons { car read-only } { cdr read-only } ;

TUPLE: empty-tuple ;

{
    [ 1 2 cons boa [ car>> ] [ cdr>> ] bi ]
    [ empty-tuple boa drop ]
    [ cons boa [ car>> ] [ cdr>> ] bi ]
    [ [ 1 cons boa ] [ 2 cons boa ] if car>> ]
    [ dup cons boa 10 [ nip dup cons boa ] each-integer car>> ]
    [ 2 cons boa { [ ] [ ] } dispatch ]
    [ dup [ drop f ] [ "A" throw ] if ]
    [ [ ] [ ] curry curry dup 3 slot swap 4 slot dup 3 slot swap 4 slot drop ]
    [ [ ] [ ] curry curry call ]
    [ <complex> <complex> dup 1 slot drop 2 slot drop ]
    [ 1 cons boa over [ "A" throw ] when car>> ]
    [ [ <=> ] sort ]
    [ [ <=> ] with search ]
} [ [ ] swap [ test-unboxing ] curry unit-test ] each

! A more complicated example
: impeach-node ( quot: ( node -- ) -- )
    dup slip impeach-node ; inline recursive

: bleach-node ( quot: ( node -- ) -- )
    [ bleach-node ] curry [ ] compose impeach-node ; inline recursive

[ ] [ [ [ ] bleach-node ] test-unboxing ] unit-test
