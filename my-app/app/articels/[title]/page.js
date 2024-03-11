export default function ShowArticelPage(props) {
    console.log(props);
    return (
        <div>
            <h1>Show Articel</h1>
            <h1>{props.params.title}</h1>
        </div>
    );
}