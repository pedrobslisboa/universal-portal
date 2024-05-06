module App = {
    [@react.component]
    let make = () => {
        UniversalPortal_Js.useRemoveServerPortals();

        <Shared_js_demo.App />
    }
}

switch (ReactDOM.querySelector("#root")) {
| Some(el) => <App /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
