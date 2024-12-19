import { sidebar } from "vuepress-theme-hope";

// 图标：https://theme-hope.vuejs.press/zh/guide/interface/icon.html#%E8%AE%BE%E7%BD%AE%E5%9B%BE%E6%A0%87
// https://fontawesome.com/search?m=free&o=r
export default sidebar(
  {
  "": [
    // 指定显示页面
    {
      text: "主要内容",
      icon: "",
      prefix: "/_posts/",
      link: "/blog",
      collapsible: false,
      children: "structure",
    },
  // 专题区（独立侧边栏）
]});
