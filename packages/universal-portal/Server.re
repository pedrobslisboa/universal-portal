module PortalCollector = {
  module Provider = {
    include React.Context;
    let make = React.Context.provider(Portal.portalCollectorContext);
  };

  [@react.component]
  let make = (~children, ~collectPortal: Portal.portal => unit) => {
    let value = {
      collectPortal;
    };

    <Provider value> children </Provider>;
  };
};

[@platform native]
let appendUniversal_Portals = (html, portals: array(Portal.portal)) => {
  let soup = html |> Soup.parse;

  Array.iter(
    (portal: Portal.portal) => {
      let markup = portal.content |> ReactDOM.renderToString |> Soup.parse;

      switch (soup |> Soup.select_one(portal.selector)) {
      | Some(titleNode) =>
        markup
        |> Soup.select_one(":root")
        |> Soup.require
        |> Soup.set_attribute("data-universal-portal", "");
        Soup.append_child(titleNode, markup);
      | None => ()
      };
    },
    portals,
  );

  let elementValue = soup |> Soup.to_string;

  elementValue;
};

[@platform native]
let collectPortals = (element, callback) => {
  <PortalCollector collectPortal={newValue => {callback(newValue)}}>
    element
  </PortalCollector>;
};

[@platform native]
let withPortals = element => {
  let portals: ref(array(Portal.portal)) = ref([||]);

  let element =
    ReactDOM.renderToString(
      collectPortals(element, (collectedPortal: Portal.portal) => {
        portals := Array.append(portals^, [|collectedPortal|])
      }),
    );

  let html = (element, portals^);

  portals := [||];

  html;
};
