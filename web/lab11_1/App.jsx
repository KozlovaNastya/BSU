import React from 'react';
import { HashRouter, Route, Switch } from 'react-router-dom';

import Layout from './components/Layout';
import Example from './components/Example/index';
import Regions from './components/Regions/index';
import MySearch from './components/MySearch/index';

const App = () => {
  return (
    <HashRouter>
      <Layout>
        <Switch>
          <Route exact path="/" component={Example} />
          <Route path="/example" component={Example} />
          <Route path="/regions" component={Regions} />
          <Route path="/mysearch" component={MySearch} />
        </Switch>
      </Layout>
    </HashRouter>
  );
};

export default App;