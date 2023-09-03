<?xml version="1.0" encoding="utf-8"?>
<rss version="2.0" 
xmlns:sparkle="http://www.andymatuschak.org/xml-namespaces/sparkle" 
xmlns:dc="http://purl.org/dc/elements/1.1/">
    <channel>
        <title>{{ site.github.project_title }}</title>
        <description>Most recent changes with links to updates.</description>
        <language>en</language>
        {% for release in site.github.releases %}
            {% unless release.draft %}
                {% unless release.prerelease and page.release_only %}
                    <item>
                        <title>{{ release.name }}</title>
                        <description><![CDATA[{{ release.body | 
markdownify }}]]></description>
                        <pubDate>{{ release.published_at | date_to_rfc822 
}}</pubDate>
                        {% for asset in release.assets limit:2 %}
                            {% if asset.name contains ".zip" == false and asset.name contains ".exe" == false %}
                            {% continue %}
                            {% endif %}

                            {% assign build_nums = asset.name | replace_first:'Tradx.v','' | replace_first:'.b',',' | remove_first:'.zip' | remove_first:'.exe' | split:',' %}
                            {% if build_nums.size == 2 %}
                                {% assign version = build_nums[0] %}
                                {% assign build_number = build_nums[1] %}
                                {% assign short_version = release.tag_name | remove_first:'v' %}
                            {% else %}
                                {% assign version = release.tag_name | remove_first:'v' %}
                            {% endif %}
                            <enclosure
                                url="{{ asset.browser_download_url }}"
                                length="{{ asset.size }}"
                                type="application/octet-stream"
                                {% if asset.name contains '.exe' %}
                                sparkle:os="windows"
                                sparkle:version="{{ version }}+{{ build_number }}"
                                {% elsif asset.name contains '.zip' %}
                                sparkle:os="macos"
                                sparkle:version="{{ version }}"
                                {% endif %}
                                {% if short_version %}sparkle:shortVersionString="{{ short_version }}"{% endif %}
                            />
                        {% endfor %}
                    </item>
                {% endunless %}
            {% endunless %}
        {% endfor %}
    </channel>
</rss>
