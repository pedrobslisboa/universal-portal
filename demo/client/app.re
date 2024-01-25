switch (ReactDOM.querySelector("#root")) {
| Some(el) => <Shared_js_demo.App /> |> ReactDOM.hydrate(_, el)
| None => ()
};
