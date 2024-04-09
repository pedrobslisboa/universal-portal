switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Shared_js_demo.App /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
