import Link from "next/link";
import Todo from "../components/todo";
export default async function PostsPage() {
    /*
    cache: "force-cache" ==> ssg
    cache: "no-store" ==> ssr
    */
    const response = await fetch('https://jsonplaceholder.typicode.com/posts',
        {
            next: {
                revalidate: 120
            }
        }
    );
    const posts = await response.json();
    const postsJSX = posts.map(post => {
        return (
            <Link href={`/posts/${post.id}`} style={{ width: "70%" }}>
                <div style={{ backgroundColor: "white", color: "black", padding: "10px", margin: "10px", width: "100%" }}>
                    <h1>{post.title}</h1>
                    <p>{post.body}</p>
                </div>
            </Link>
        )
    })
    console.log(posts);
    return (
        <div>
            <h1>Posts Page</h1>
            {/* Start Posts */}
            <div style={{ display: "flex", justifyContent: "center", alignItems: "center", flexDirection: "column" }}>
                {postsJSX}
            </div>
            {/* End Posts */}
        </div>
    );
}