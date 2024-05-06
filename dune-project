(lang dune 3.8)

(using melange 0.1)

(name universal-portal)

(license MIT)

(maintainers "Pedro B S Lisboa <pedrobslisboa@gmail.com>")

(authors "Pedro B S Lisboa <pedrobslisboa@gmail.com>")

(source
 (github pedrobslisboa/universal-portal))

(generate_opam_files true)

(implicit_transitive_deps false)

(package
 (name universal-portal)
 (synopsis "Universal Portal for ssr natively ReasonReact apps")
 (depends
  (ocaml
   (>= 5.0.0))
  (reason
   (>= 3.10.0))
  melange
  melange-webapi
  dream
  quickjs
  (reason-react-ppx
   (>= 0.14.0))
  (reason-react
   (>= 0.14.0))
  lambdasoup
  ;; Test dependencies
  (alcotest :with-test)
  (alcotest-lwt :with-test)
  (fmt :with-test)
  ;; Dev dependencies
  (ocamlformat
   (and
    (= 0.26.1)
    :with-test))
  (server-reason-react
   (= 0.2.0))
  (melange-testing-library :with-test)
  (melange-jest :with-test)
  (ocaml-lsp-server :with-test)))
