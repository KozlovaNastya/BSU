import React, { useState, useEffect } from "react";
import "./styles.css";

/**
 * Since this component shows code we include the https://prismjs.com/
 * formatter. We invoke it by labelling code blocks with class="language-jsx"
 */
import Prism from "prismjs";
import "prismjs/components/prism-jsx.js";
import "../../node_modules/prismjs/themes/prism.css";

// Functional Component Example
const Example = () => {
  // Все состояния через useState
  const [name] = useState(window.lab1models.exampleModel().name);
  const [counter, setCounter] = useState(0);
  const [motto, setMotto] = useState(" Первый React компонент");
  
  // useEffect для timer (замена componentDidMount + componentWillUnmount)
  useEffect(() => {
    // Функция для увеличения счетчика
    const counterIncrFunc = () => {
      setCounter(prevCounter => prevCounter + 1);
    };
    
    // Запускаем интервал
    const timerID = setInterval(counterIncrFunc, 2 * 1000);
    
    // Запускаем подсветку кода
    Prism.highlightAll();
    
    // Cleanup function (замена componentWillUnmount)
    return () => {
      clearInterval(timerID);
    };
  }, []); // Пустой массив зависимостей = эффект только при монтировании

  // useEffect для подсветки кода при обновлении
  useEffect(() => {
    Prism.highlightAll();
  }, [motto]); // Запускается при изменении motto

  // Обработчики событий
  const handleMottoChange = (event) => {
    setMotto(event.target.value);
  };

  return (
    <div className="container Example">
      <h1>lab1 React.js Example</h1>

      <div className="motto-update">
        {motto}
      </div>

      <div className="lab1-example-output">
        <label htmlFor="mottoId">Change the motto:</label>
        <input
          id="mottoId"
          type="text"
          value={motto}
          onChange={handleMottoChange}
        />
      </div>

      <p>
        This view is an example of a &nbsp;
        <a
          href="https://react.dev/reference/react/Component"
          target="_blank"
          rel="noopener noreferrer"
        >
          React.js Component
        </a>
        &nbsp; named <span className="lab1-code-name">Example</span>. It is
        located in the file <code>components/Example/index.jsx</code>. It
        looks like a JavaScript class named Example that has a method named
        named <span className="lab1-code-name">render</span>, which appears
        to written in something that looks like HTML.
      </p>
      <p>
        It is actually written in a language named &nbsp;
        <a
          href="https://reactjs.org/docs/introducing-jsx.html"
          target="_blank"
          rel="noopener noreferrer"
        >
          JSX
        </a>
        &nbsp; that is run as a preprocessor to the HTML-like language to
        JavaScript. The generated JavaScipt is limited to calls to the
        React.js &nbsp;
        <a
          href="https://reactjs.org/docs/react-api.html#createelement"
          target="_blank"
          rel="noopener noreferrer"
        >
          createElement
        </a>
        &nbsp; function which allow us to write something that looks like HTML
        to describe what the component renders.
      </p>
      <p>
        Although JSX looks like HTML, it is not HTML. Some of the differences
        are necessary due to embeddding in JavaScript. For example, rather
        than <code>class=</code> we use <code>className=</code> (class is a
        JavaScript keyword). Although it is possible to interleave JavaScript
        and JSX code, care is needed since contents of JSX tags are processed
        into arguments to a function limiting what can be done as will be seen
        below.
      </p>

      <h3>Template substitution</h3>

      <p>
        JSX treats text inside of parentheses (e.g.{" "}
        <code>{"{JavaScriptExpression}"}</code>) as templates where the
        JavaScript expression is evaluated in the context of the current
        function and whose value replaces the template in the string. The
        expression can evaluate to a JavaScript string or value from a JSX
        expression. This feature allows component&apos;s specification to use
        templated HTML.
      </p>

      <p>
        The Example class constructor sets the object&apos;s property{" "}
        <code>state.name</code> (see the assignment to{" "}
        <code>this.state.name</code> in <code>Example.jsx</code>) from the
        model in the DOM which has a value of &ldquo; {name} &rdquo; so:
      </p>
      <pre className="lab1-example-code">
        <code className="language-jsx">
          {`<p>My name is "{name}".</p>`}
        </code>
      </pre>
      <p>should render as:</p>
      <p className="lab1-example-output">
        My name is &ldquo; {name} &rdquo;.
      </p>
    </div>
  );
};

export default Example;