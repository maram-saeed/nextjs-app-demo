import Link from "next/link";

export default function Articels() {
    return (
        <div>
            <h1>Articels Page</h1>

            <Link href="/posts">
                <button>click to Posts Page</button>
            </Link>
        </div>
    );
}