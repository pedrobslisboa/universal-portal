open Jest;
open Webapi.Dom;
open Webapi.Dom.Element;
open Document;
open ReactTestingLibrary;
open DomTestingLibrary;

module AppWithPortalCleaner = {
  [@react.component]
  let make = () => {
    UniversalPortal.UseRemoveServerPortals.make();

    <div id="root">
      {"Hello World" |> React.string}
      <UniversalPortal.Portal selector="body">
        <div> {React.string("Portal Content")} </div>
      </UniversalPortal.Portal>
    </div>;
  };
};

Expect.(
  describe("Shared.", () => {
    let portalComponent =
      <div id="root">
        {"Hello World" |> React.string}
        <UniversalPortal.Portal selector="body">
          <div> {React.string("Portal Content")} </div>
        </UniversalPortal.Portal>
      </div>;

    test("getByLabelText works", () => {
      render(portalComponent) |> ignore;

      (
        switch (querySelector("body", document)) {
        | Some(element) => element |> innerHTML
        | None => ""
        }
      )
      |> expect
      |> toBe(
           "<div><div id=\"root\">Hello World</div></div><div>Portal Content</div>",
         );
    });

    testPromise("getByLabelText works", () => {
      render(<AppWithPortalCleaner />) |> ignore;

      let callback = () => {
        let _ =
          (
            switch (querySelector("body", document)) {
            | Some(element) => element |> innerHTML
            | None => ""
            }
          )
          |> expect
          |> not
          |> toBe(
               "<div><div id=\"root\">Hello World</div></div><div>Portal Content</div>",
             );

        ();
      };

      waitFor(~callback, ())
      |> Js.Promise.then_(_ => Js.Promise.resolve(pass));
    });
  })
);
