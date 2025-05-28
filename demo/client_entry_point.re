module App = {
  [@react.component]
  let make = () => {
    UniversalPortal.UseRemoveServerPortals.make();

    <App />;
  };
};

switch (ReactDOM.querySelector("#root")) {
| Some(el) => <App /> |> ReactDOM.Client.hydrateRoot(el) |> ignore
| None => ()
};
